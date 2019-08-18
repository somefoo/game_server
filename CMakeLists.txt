cmake_minimum_required(VERSION 3.0.0)

#ADD_SUBDIRECTORY(src)
project(game_server VERSION 0.1.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${game_server_SOURCE_DIR}/cmake")

ADD_SUBDIRECTORY(server)
