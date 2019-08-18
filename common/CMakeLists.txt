if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

file(GLOB common_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_library(common STATIC ${common_SRC})
set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)

#External view
set(COMMON_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
set(COMMON_LIBRARIES common PARENT_SCOPE)
