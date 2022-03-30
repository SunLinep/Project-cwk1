cmake_minimum_required(VERSION 3.21)
project(book C)

set(CMAKE_C_STANDARD 99)

include_directories(book_management.h user.h)

add_executable(book main.c user.c user.h book_management.c book_management.h books.c books.h)