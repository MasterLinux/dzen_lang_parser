cmake_minimum_required(VERSION 2.8.4)
project(dzen_lang_parser)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES test/minunit.h test/tests.c src/dzen_parser.c src/dzen_list.c)
add_executable(dzen_lang_parser ${SOURCE_FILES})