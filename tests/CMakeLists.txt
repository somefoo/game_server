if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#POSIX threads have trouble in these envs. test on linux only!
if(LINUX)
message(STATUS "Building tests...")
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

include_directories(common)
include_directories(server)
include_directories(client)

add_executable(connection_test connection_test.cpp)
target_link_libraries(connection_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(Connection_Test connection_test)


add_executable(send_packet_test send_packet_test.cpp)
target_link_libraries(send_packet_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(Send_Packet_Test send_packet_test)


add_executable(poll_test poll_test.cpp)
target_link_libraries(poll_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(Poll_Test poll_test)


#NOT A TEST
add_executable(start_server start_server.cpp)
target_link_libraries(start_server PRIVATE ${THREADS_LIBRARIES} common server client)
endif(LINUX)
