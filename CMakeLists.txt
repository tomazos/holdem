cmake_minimum_required(VERSION 3.9)
project(holdem)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall)
add_compile_options(-Werror)
add_compile_options(-O2)

add_library(stdc++fs UNKNOWN IMPORTED)
set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION "/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++fs.a")

add_executable(holdem main.cpp face.cpp suit.h suit.cpp card.h card.cpp util.h fivecards.h fivecards.cpp rank.h rank.cpp)

target_link_libraries(${PROJECT_NAME} stdc++fs)