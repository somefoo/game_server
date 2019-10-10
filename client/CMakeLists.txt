if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O2 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -g -Wall -Wextra")

file(GLOB client_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
)

#find_package(ENet REQUIRED)

message(STATUS ${CENET_INCLUDE_DIRS})
#Create lib
add_library(client STATIC ${client_SRC})
set_target_properties(client PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(client PUBLIC ${COMMON_INCLUDE_DIRS})
target_include_directories(client PUBLIC enet)
target_link_libraries(client PUBLIC enet ${COMMON_LIBRARIES})

#External view
set(CLIENT_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
set(CLIENT_LIBRARIES client PARENT_SCOPE)
