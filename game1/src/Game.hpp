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
    const bool getEndGame() const;

    // Functions
    void spawnEnemy();

    void pollEvents();

    void updateMousePos();
    void updateEnemies();
    void updateText();
    void update();

    void renderEnemies(sf::RenderTarget& target);
    void renderText(sf::RenderTarget& target);
    void render();

private:
    // Variables
    // Window stuff
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Mouse pos (relative to game window)
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Resources
    sf::Font fontDosisLight;

    // Text
    sf::Text uiText;

    // Game logic
    bool endGame;
    unsigned points;
    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    // Game objs
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private functions    
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();
};