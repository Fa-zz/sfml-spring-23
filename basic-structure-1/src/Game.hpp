#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    Class that acts as game engine. Wrapper class.
*/

class Game {
public:
    // Constructors
    Game();
    virtual ~Game();

    // Accessors
    const bool running() const;

    // Functions
    void pollEvents();
    void update();
    void render();

private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Private functions
    void initVariables();
    void initWindow();
};