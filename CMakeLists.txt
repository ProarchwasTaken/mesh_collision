cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER clang++)

project("program")
include_directories("include")
set(EXECUTABLE_OUTPUT_PATH "../")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable("program" src/main.cpp src/player.cpp include/player.h)
target_compile_options("program" PRIVATE --debug)
target_link_libraries("program" PRIVATE
-static
-static-libgcc 
-static-libstdc++
-lraylib 
-lopengl32 
-lgdi32
-lwinmm
)

