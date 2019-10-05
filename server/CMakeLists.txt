if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -g -Wall -Wextra")

file(GLOB server_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
)

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

find_package(OpenMP REQUIRED)
find_package(Threads REQUIRED)


#Create lib
add_library(server STATIC ${server_SRC})
set_target_properties(server PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(server PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${OpenMP_CXX_LIBRARIES} ${CENET_LIBRARIES} ${COMMON_LIBRARIES} ${CLIENT_LIBRARIES})

target_include_directories(server PRIVATE ${OPENMP_INCLUDE_DIRS})
target_include_directories(server PRIVATE ${THREADS_INCLUDE_DIRS})
#My libs
target_include_directories(server PRIVATE ${COMMON_INCLUDE_DIRS})
target_include_directories(server PRIVATE ${CLIENT_INCLUDE_DIRS})
target_include_directories(server PRIVATE ${CENET_INCLUDE_DIRS})

#External view
set(SERVER_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
set(SERVER_LIBRARIES server PARENT_SCOPE)
