#pragma once

#include <iostream>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game {
private:
    sf::VideoMode videoMode;    // videoMode: Holds size, width+height of window
    sf::RenderWindow* window;   
    bool endGame;               // endGame: flag to determine when game should end
    sf::Event sfmlEvent;        // sfmlEvent: Gets event from mouse, keyboard, window etc 

    // Initializer functions
    void initVariables();
    void initWindow();

public:
    // Constructors and destructors
    Game();
    ~Game();

    // Accessors

    // Modifiers

    // Functions
    const bool running() const;     // Returns whether game window is open
    void pollEvents();

    void update();
    void render();
};