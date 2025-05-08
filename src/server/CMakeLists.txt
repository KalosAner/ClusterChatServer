aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)
aux_source_directory(./buffer BUFFER_LIST)
aux_source_directory(./log LOG_LIST)

add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST} ${BUFFER_LIST} ${LOG_LIST})

target_link_libraries(ChatServer muduo_net muduo_base mysqlclient hiredis pthread)