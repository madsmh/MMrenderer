cmake_minimum_required(VERSION 3.10.2)
project(MMrenderer)

set(CMAKE_CXX_STANDARD 14)

FIND_PACKAGE( Boost 1.65 COMPONENTS REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(MMrenderer main.cpp object.h ray.h scene.h sphere.h vector3.h camera.h )

find_package(Gosu REQUIRED development)
include_directories(${GOSU_INCLUDE_DIRS})
target_link_libraries(MMrenderer ${GOSU_LIBRARIES})

