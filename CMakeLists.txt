cmake_minimum_required(VERSION 3.14)
project(MMrenderer)

set(CMAKE_CXX_STANDARD 14)

add_executable(MMrenderer main.cpp vector3.h scene.h camera.h solid.h ray.h)