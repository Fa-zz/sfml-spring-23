#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Engine {
public:
    // Constructors
    Engine();
    virtual ~Engine();

    // Accessors
    const bool running() const;
    const bool getEndGame() const;

    // Functions
    void pollEvents();
    void updateMousePos();
    void updateCamera();
    void updateObjs();
    void update();

    void renderObjs(sf::RenderTarget& target);
    void render();

private:
    // Variables
    // Window stuff
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Clock
    float dt = 0.f;
    sf::Clock dtClock;

    // View
    sf::View view;
    float viewSpeed;

    // Mouse pos (relative to game window)
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Logic
    float gravity;
    float gridSizeF;
    unsigned gridSizeU;
    bool endGame;
    bool mouseHeld;

    // Objects
    sf::RectangleShape shape;
    sf::RectangleShape ground;
    std::vector<sf::RectangleShape> objects;

    // Private functions    
    void initVariables();
    void initWindow();
    void initView();
    void initObjs();
};