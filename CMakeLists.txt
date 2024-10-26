cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_NAME TapeSorter)

project(${PROJECT_NAME})

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "tmp")

add_executable(${PROJECT_NAME}
    tape/main.cpp
    tape/tape_devices/TapeDeviceInterface.h
    tape/tape_devices/TapeDeviceSorter.h
    tape/tape_devices/TapeDeviceSorter.cpp
    tape/sort_tape_algorithms/SortOfTapeInterface.h
    tape/sort_tape_algorithms/SortOfTapeWithLimitRAM.h
    tape/sort_tape_algorithms/SortOfTapeWithLimitRAM.cpp
    tape/exceptions/OpenFileException.h
    tape/exceptions/OpenFileException.cpp
    tape/exceptions/SortSizeException.h
    tape/exceptions/SortSizeException.cpp
)
