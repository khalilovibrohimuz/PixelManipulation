cmake_minimum_required(VERSION 3.22.1)

project("glecy")

add_library(${CMAKE_PROJECT_NAME} SHARED
        glecy.cpp)

find_library(
        log-lib
        log)

find_library(jnigraphics-lib jnigraphics)


target_link_libraries(
        glecy
        ${log-lib}
        ${jnigraphics-lib})
