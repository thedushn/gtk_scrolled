cmake_minimum_required(VERSION 3.7)
project(gtk_scrolled_window)

set(CMAKE_C_STANDARD 99)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(SOURCE_FILES main.c drawing.c drawing.h reading.c reading.h common.h)
add_executable(gtk_scrolled_window ${SOURCE_FILES})

include_directories(${GTK3_INCLUDE_DIRS})

link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})
link_directories(${GTK3_LIBRARY_DIRS})
link_libraries(${GTK3_LIBRARIES})

target_link_libraries(gtk_scrolled_window ${GTK3_LIBRARIES})
target_link_libraries(gtk_scrolled_window m)
