#include "game.h"
#include <iostream>
#include <exception>

int main() {
    try {
        // Create and initialize the game
        Game game;
        
        if (!game.initialize()) {
            std::cerr << "Failed to initialize game!" << std::endl;
            std::cerr << "Make sure you're running this in a Windows console." << std::endl;
            std::cout << "Press any key to exit..." << std::endl;
            std::cin.get();
            return 1;
        }
        
        // Run the game
        game.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Press any key to exit..." << std::endl;
        std::cin.get();
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        std::cout << "Press any key to exit..." << std::endl;
        std::cin.get();
        return 1;
    }
    
    return 0;
}
