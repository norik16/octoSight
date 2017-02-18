cmake_minimum_required(VERSION 2.8.0)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arduino/Arduinotoolchain.cmake)
set(PROJECT_NAME main)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_BOARD mega)
set(${CMAKE_PROJECT_NAME}_port /dev/ttyUSB0)

set(${CMAKE_PROJECT_NAME}_SKETCH /src/octoSight/octoSight.ino)
#generate_arduino_firmware(${CMAKE_PROJECT_NAME})