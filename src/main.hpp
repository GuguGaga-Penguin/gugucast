#include <iostream>
#include <SDL3/SDL.h>
#include "memory.hpp"

// Setup 60Hz loop cycle frames (200 MHz CPU / 60 Frames Per Second)
const int REFRESH_TICK_CYCLES = 3333333; 

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == false) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Dreamcast Native Emulator (No WASM Mode)", 640, 480, 0);
    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    SystemMemory memory;
    if (!memory.AllocateHardwareBuffers()) {
        std::cerr << "Fatal Error: Host system refused direct memory mapping requests." << std::endl;
        return -1;
    }

    std::cout << "Direct System OS RAM Allocated: 0x" << std::hex << (uintptr_t)memory.native_ram_ptr << std::endl;

    bool app_running = true;
    SDL_Event native_event;

    // Platform execution engine cycle frame loop
    while (app_running) {
        while (SDL_PollEvent(&native_event)) {
            if (native_event.type == SDL_EVENT_QUIT) {
                app_running = false;
            }
        }

        // --- Native CPU Recompiler Tick Block ---
        int spent_cycles = 0;
        while (spent_cycles < REFRESH_TICK_CYCLES) {
            // Your native execution steps run here
            spent_cycles += 4; 
        }

        // Send finished render grids straight to screen buffer
    }

    memory.FreeHardwareBuffers();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
