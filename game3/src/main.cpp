#include <iostream>
#include "Engine.hpp"

int main() {

    // Init rand seed
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game engine
    Engine engine;

    // Game loop
    while (engine.running() && !engine.getEndGame()) {

        // Update
        engine.update();

        // Render
        engine.render();
    }

    // End of application

    return 0;
}