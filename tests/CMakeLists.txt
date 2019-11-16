if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#POSIX threads have trouble in these envs. test on linux only!
if(UNIX)
message(STATUS "Building tests...")
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

add_executable(connection_test connection_test.cpp)
target_link_libraries(connection_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(Connection_Test connection_test)


add_executable(send_packet_test send_packet_test.cpp)
target_link_libraries(send_packet_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(Send_Packet_Test send_packet_test)


add_executable(poll_test poll_test.cpp)
target_link_libraries(poll_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(Poll_Test poll_test)

add_executable(external_view_test external_view_test.cpp)
target_link_libraries(external_view_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(External_View_Test external_view_test)

add_executable(player_state_test player_state_test.cpp)
target_link_libraries(player_state_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(Player_State_Test player_state_test)

add_executable(packet_wrapper_test packet_wrapper_test.cpp)
target_link_libraries(packet_wrapper_test PRIVATE ${THREADS_LIBRARIES} common server client)
add_test(Packet_Wrapper_Test packet_wrapper_test)

#NOT A TEST
add_executable(start_server start_server.cpp)
target_link_libraries(start_server PRIVATE ${THREADS_LIBRARIES} common server client)
endif(UNIX)
