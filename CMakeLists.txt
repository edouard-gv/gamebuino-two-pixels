cmake_minimum_required(VERSION 3.15)
project(twopixels)

set(CMAKE_CXX_STANDARD 14)

add_executable(twopixels twopixels.ino)
include_directories(TwoPixels_lib)
add_subdirectory(TwoPixels_lib)

add_subdirectory(Google_test)

target_link_libraries(twopixels TwoPixels_lib)
