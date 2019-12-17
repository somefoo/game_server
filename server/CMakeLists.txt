if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Og -Wall -Wextra")

find_package(OpenMP REQUIRED)
find_package(Threads REQUIRED)


#Create lib
add_library(server STATIC)
target_sources(server
  PRIVATE
    "src/server.cpp"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/server.h"
  )
set_target_properties(server PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(server PUBLIC ${OPENMP_INCLUDE_DIRS})
target_include_directories(server PUBLIC ${THREADS_INCLUDE_DIRS})
#My libs
target_include_directories(server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(server PUBLIC game PRIVATE ${CMAKE_THREAD_LIBS_INIT} ${OpenMP_CXX_LIBRARIES} enet common client)
