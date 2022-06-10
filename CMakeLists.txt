cmake_minimum_required(VERSION 3.5)

project(logger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(OS_WIN)
#add_compile_definitions(OS_LINUX)

set(headers logger.h stream_writer.h console_stream_writer.h file_stream_writer.h)
set(cpp logger.cpp console_stream_writer.cpp file_stream_writer.cpp)

add_library(logger STATIC ${headers} ${cpp})
