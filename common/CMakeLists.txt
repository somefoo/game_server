if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -g -Wall -Wextra")

file(GLOB common_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_library(common STATIC ${common_SRC})
set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)
#target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#External view
set(COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
set(COMMON_LIBRARIES common PARENT_SCOPE)
