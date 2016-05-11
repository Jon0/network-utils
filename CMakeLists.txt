cmake_minimum_required (VERSION 2.6)


# project name
set(CORE_LIBRARY_NAME "network-utils")
project("${CORE_LIBRARY_NAME}")


# std threads
find_package(Threads REQUIRED)


# include src
include_directories("${PROJECT_SOURCE_DIR}/")


# build core library
add_subdirectory(src)


#build executable
add_subdirectory(bin)
