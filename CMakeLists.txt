cmake_minimum_required(VERSION 3.22)
project(DreamcastNativeWinApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force high-speed compiler loops and optimization flags inside Windows MSVC
if(MSVC)
    add_compile_options(/O2 /Oi /Ot /GF /MP)
    # Hide the ugly black diagnostic command window when launching your graphics app
    set(WINDOWS_SUBSYSTEM_LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

# Bind structural engine component paths together
add_executable(native_dc_emu
    src/main.cpp
    src/cpu_jit.cpp
)

# Instruct Windows to treat this binary explicitly as an interactive window application
if(MSVC)
    set_target_properties(native_dc_emu PROPERTIES LINK_FLAGS "${WINDOWS_SUBSYSTEM_LINK_FLAGS}")
endif()

