/*
Proof of concept for enabling/disabling global debug flags at runtime
in addition to compile-time debug flags defined via preprocessor directives.

Run `g++ test.cpp && ./a.out` or `g++ test.cpp && ./a.out --graphics-debug`

*/
#include <unordered_map>
#include <string>
#include <iostream>

std::unordered_map<std::string, bool> debug_flags;
bool graphicsDebugEnabled = false;

// preprocessor directive reads from some sort of command line flag (?)
#define DEBUG_MODE true

void debug_operation() {
    std::cout << "Expensive Debug Operation" << std::endl;
}

void init_debug_flags() {
    // initialize map of flags
    debug_flags["GRAPHICS_DEBUG"] = false;
}

int main(int argc, char* argv[]) {
    // map has to be populated in a main function/function
    init_debug_flags();

    // Simulate populating debug_flags map from Redis channel
    // by parsing command-line arguments
    for (int i = 1; i < argc; ++i) { // Start from 1 to skip program name (argv[0])
        std::string arg = argv[i];
        if (arg == "--graphics-debug") {

            // simulate populating map entry from Redis channel
            debug_flags["GRAPHICS_DEBUG"] = true;
        }
    }

    if (DEBUG_MODE) {
        // query Redis channel for debug flag
        graphicsDebugEnabled = debug_flags["GRAPHICS_DEBUG"]; 
        if (graphicsDebugEnabled) {
            debug_operation();
        }
    }

    return 0;
}
