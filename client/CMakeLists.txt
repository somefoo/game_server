if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Og -Wall -Wextra")

#Create lib
add_library(client STATIC)
target_sources(client
  PRIVATE 
    "src/client.cpp"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/client.h"
  )
set_target_properties(client PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
#target_include_directories(client PRIVATE enet)
#target_include_directories(client PRIVATE common)
target_link_libraries(client PUBLIC enet game PRIVATE common)

get_target_property(cheese client INCLUDE_DIRECTORIES)
message(STATUS ${cheese})
