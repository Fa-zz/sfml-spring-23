#pragma once

#include <iostream>
#include <unistd.h>
#include <cmath>

#include "Tank.hpp"

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
    float dt = 0.f;
    float elapsed;
    float timeNow;
    float accumulator;
    float timestep;

    //Logic
    float groundStart;
    float moveSpeed;
    float rotateBy;
    bool chargedUp;
    float initVel;
    float initAngle;
    float maxHeight, gravity, timeToReachMaxHeight, distAtMaxHeight;
    float initVelY, initVelX;
    bool projectileInAir;
    float afterVelY;
    bool endGame;

    // Objects
    sf::RectangleShape ground;
    std::vector<Tank*> tanks;
    std::vector<sf::CircleShape*> projectiles;
    sf::CircleShape *projectile;

    // Private functions    
    void initVariables();
    void initWindow();
    void initView();
    void initElems();
};