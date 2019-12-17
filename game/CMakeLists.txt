if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O3 -Wall -Wextra -Werror -Wno-unused-private-field")
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Og -Wall -Wextra")

file(GLOB game_SRC
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_library(game STATIC ${game_SRC})
set_target_properties(game PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game PRIVATE common)

#External view
set(GAME_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)
set(GAME_LIBRARIES game PARENT_SCOPE)
