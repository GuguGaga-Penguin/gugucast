#pragma once
#include <cstdint>
#include <iostream>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <sys/mman.h>
#endif

class SystemMemory {
public:
    uint8_t* native_ram_ptr = nullptr;
    uint8_t* native_vram_ptr = nullptr;

    bool AllocateHardwareBuffers() {
        size_t ram_size = 16 * 1024 * 1024; // 16 MB Main RAM
        size_t vram_size = 8 * 1024 * 1024; // 8 MB VRAM

#if defined(_WIN32)
        // Request pages directly from Windows Virtual Memory Engine
        native_ram_ptr = (uint8_t*)VirtualAlloc(NULL, ram_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        native_vram_ptr = (uint8_t*)VirtualAlloc(NULL, vram_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
        // Request pages directly from POSIX Linux / macOS Kernel Allocators
        native_ram_ptr = (uint8_t*)mmap(NULL, ram_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        native_vram_ptr = (uint8_t*)mmap(NULL, vram_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
#endif

        return (native_ram_ptr != nullptr && native_vram_ptr != nullptr);
    }

    void FreeHardwareBuffers() {
#if defined(_WIN32)
        if (native_ram_ptr) VirtualFree(native_ram_ptr, 0, MEM_RELEASE);
        if (native_vram_ptr) VirtualFree(native_vram_ptr, 0, MEM_RELEASE);
#else
        if (native_ram_ptr) munmap(native_ram_ptr, 16 * 1024 * 1024);
        if (native_vram_ptr) munmap(native_vram_ptr, 8 * 1024 * 1024);
#endif
    }
};
