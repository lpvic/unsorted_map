cmake_minimum_required(VERSION 3.5.0)
project(unsorted_map VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(mylibs "~/Programacion/_libraries/C++")
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(mylibs "C:/Users/luisp/Programacion/_libraries/C++")
endif()

include_directories(include)
add_subdirectory(tests)
