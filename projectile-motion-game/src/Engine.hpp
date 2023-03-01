#pragma once

#include <iostream>
#include <unistd.h>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Engine {
public:
    // Constructors
    Engine();
    ~Engine();

    // Accessors
    const bool running() const;
    const bool getEndGame() const;

    // Update and render Functions
    void pollEvents();
    void updateCamera();
    void playerInput();
    void updateObjs();
    void update();

    void renderObjs(sf::RenderTarget& target);
    void render();

private:
    // Window stuff
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // View stuff
    sf::View view;
    float viewSpeed;

    // Time
    sf::Clock clock;
    float elapsed;

    //Logic
    float initAngle;
    float initVel;
    float initVelY, initVelX;
    bool endGame;

    // Private functions    
    void initVariables();
    void initWindow();
    void initView();
    void initElems();
};