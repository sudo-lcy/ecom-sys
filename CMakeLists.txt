cmake_minimum_required(VERSION 3.10)
project(ecom-sys LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC src/main.cpp)
add_executable(ecommerce ${SRC})
