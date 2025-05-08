 #include "buffer.h"

MyBuffer::MyBuffer(int initBuffSize) : buffer_(initBuffSize), readPos_(0), writePos_(0) {}

size_t MyBuffer::ReadableBytes() const {  // 可以读的数据的大小
    return writePos_ - readPos_;
}
size_t MyBuffer::WritableBytes() const {
    return buffer_.size() - writePos_;
}

// 前面可以用的空间
size_t MyBuffer::PrependableBytes() const {
    return readPos_;
}

const char* MyBuffer::Peek() const {
    return BeginPtr_() + readPos_;
}

void MyBuffer::Retrieve(size_t len) {
    assert(len <= ReadableBytes());
    readPos_ += len;
}

//buff.RetrieveUntil(lineEnd + 2);
void MyBuffer::RetrieveUntil(const char* end) {
    assert(Peek() <= end );
    Retrieve(end - Peek());
}

void MyBuffer::RetrieveAll() {
    bzero(&buffer_[0], buffer_.size());
    readPos_ = 0;
    writePos_ = 0;
}

std::string MyBuffer::RetrieveAllToStr() {
    std::string str(Peek(), ReadableBytes());
    RetrieveAll();
    return str;
}

const char* MyBuffer::BeginWriteConst() const {
    return BeginPtr_() + writePos_;
}

char* MyBuffer::BeginWrite() {
    return BeginPtr_() + writePos_;
}

void MyBuffer::HasWritten(size_t len) {
    writePos_ += len;
} 

void MyBuffer::Append(const std::string& str) {
    Append(str.data(), str.length());
}

void MyBuffer::Append(const void* data, size_t len) {
    assert(data);
    Append(static_cast<const char*>(data), len);
}

//  Append(buff, len - writable);   buff临时数组，len-writable是临时数组中的数据个数
void MyBuffer::Append(const char* str, size_t len) {
    assert(str);
    EnsureWriteable(len);
    std::copy(str, str + len, BeginWrite());
    HasWritten(len);
}

void MyBuffer::Append(const MyBuffer& buff) {
    Append(buff.Peek(), buff.ReadableBytes());
}

void MyBuffer::EnsureWriteable(size_t len) {
    if(WritableBytes() < len) {
        MakeSpace_(len);
    }
    assert(WritableBytes() >= len);
}

ssize_t MyBuffer::ReadFd(int fd, int* saveErrno) {
    
    char buff[65535];   // 临时的数组，保证能够把所有的数据都读出来
    
    struct iovec iov[2];
    const size_t writable = WritableBytes();
    
    /* 分散读， 保证数据全部读完 */
    iov[0].iov_base = BeginPtr_() + writePos_;
    iov[0].iov_len = writable;
    iov[1].iov_base = buff;
    iov[1].iov_len = sizeof(buff);

    const ssize_t len = readv(fd, iov, 2);
    if(len < 0) {
        *saveErrno = errno;
    }
    else if(static_cast<size_t>(len) <= writable) {
        writePos_ += len;
    }
    else {
        writePos_ = buffer_.size();
        Append(buff, len - writable);
    }
    return len;
}

ssize_t MyBuffer::WriteFd(int fd, int* saveErrno) {
    size_t readSize = ReadableBytes();
    ssize_t len = write(fd, Peek(), readSize);
    if(len < 0) {
        *saveErrno = errno;
        return len;
    } 
    readPos_ += len;
    return len;
}

char* MyBuffer::BeginPtr_() {
    return &*buffer_.begin();
}

const char* MyBuffer::BeginPtr_() const {
    return &*buffer_.begin();
}

void MyBuffer::MakeSpace_(size_t len) {
    if(WritableBytes() + PrependableBytes() < len) {
        buffer_.resize(writePos_ + len + 1);
    } 
    else {
        size_t readable = ReadableBytes();
        std::copy(BeginPtr_() + readPos_, BeginPtr_() + writePos_, BeginPtr_());
        readPos_ = 0;
        writePos_ = readPos_ + readable;
        assert(readable == ReadableBytes());
    }
}