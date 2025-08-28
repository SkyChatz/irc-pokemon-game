cmake_minimum_required(VERSION 3.10)

project(irc_pokemon_game)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(irc_pokemon_game ${SOURCES})