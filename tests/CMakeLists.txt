if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

include_directories(${COMMON_INCLUDE_DIRS})
include_directories(${SERVER_INCLUDE_DIRS})
include_directories(${CLIENT_INCLUDE_DIRS})

add_executable(connection_test connection_test.cpp)
target_link_libraries(connection_test PRIVATE ${COMMON_LIBRARIES} ${SERVER_LIBRARIES} ${CLIENT_LIBRARIES})
add_test(Connection_Test connection_test)
