if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

file(GLOB client_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
)
include_directories(${COMMON_INCLUDE_DIRS})

#Create lib
add_library(client STATIC ${client_SRC})
set_target_properties(client PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(client PRIVATE ${COMMON_LIBRARIES})

#External view
set(CLIENT_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
set(CLIENT_LIBRARIES client PARENT_SCOPE)
