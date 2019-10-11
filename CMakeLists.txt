cmake_minimum_required(VERSION 3.12)

#ADD_SUBDIRECTORY(src)
project(game_server VERSION 0.1.0)
#set(COMMON_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/common")
#set(CLIENT_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/client")

#set(CENET_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/lib/enet/include/")

#if(UNIX)
#  set(CENET_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/enet/libenet.a")
#endif(UNIX)

#if(MSVC OR MSYS OR MINGW OR WIN32)
#  set(CENET_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/enet/enet64.lib")
#endif(MSVC OR MSYS OR MINGW OR WIN32)

#if(APPLE)
#message(ERROR "No lib for MacOS yet, compile first and add here.")
#endif(APPLE)

ADD_SUBDIRECTORY(lib/enet)
ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(client)
ADD_SUBDIRECTORY(server)
ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)
