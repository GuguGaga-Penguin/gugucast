cmake_minimum_required(VERSION 3.20)
project(NativeDreamcastEmulator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure build styles targeting aggressive architectural hardware performance rules
if(MSVC)
    add_compile_options(/O2 /Oi /Ot /Oi)
else()
    add_compile_options(-O3 -march=native -flto)
endif()

# Locate standard native framework engine libraries installed locally on your system
find_package(SDL3 REQUIRED)

add_executable(native_dc_emu 
    src/main.cpp
)

target_link_libraries(native_dc_emu PRIVATE SDL3::SDL3)
