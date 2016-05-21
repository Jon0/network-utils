cmake_minimum_required (VERSION 2.6)


# project name
set(PROJECT_NAME "network-utils")
project("${PROJECT_NAME}")


# lib names
set(NET_LIBRARY_NAME "libnet")
set(PROT_LIBRARY_NAME "libprot")
set(UNIX_LIBRARY_NAME "libunix")
set(UTIL_LIBRARY_NAME "libutil")


# std threads
find_package(Threads REQUIRED)


# include src
include_directories("${PROJECT_SOURCE_DIR}/")


# build core libraries
add_subdirectory(libutil)
add_subdirectory(libunix)
add_subdirectory(libprot)
add_subdirectory(libnet)

#build executable
add_subdirectory(bin)
