cmake_minimum_required(VERSION 3.5)

project(test_logger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(headers logger.h stream_writer.h console_stream_writer.h file_stream_writer.h file.h)
set(cpp logger.cpp console_stream_writer.cpp file_stream_writer.cpp file.cpp)

add_library(logger STATIC ${headers} ${cpp})
