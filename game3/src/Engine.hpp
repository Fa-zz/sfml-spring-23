#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include "Object.hpp"

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
    void spawnObjs();
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
    Object circle;
    sf::RectangleShape ground;
    std::vector<Object> objects;

    // Private functions    
    void initVariables();
    void initWindow();
    void initView();
    void initElems();
};