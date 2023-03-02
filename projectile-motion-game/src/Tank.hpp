#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Tank {
public:
    // Constructor
    Tank();

    // Destructor
    ~Tank();

    void setPosition(sf::Vector2f tankPosition);
    void setColor(sf::Color color);
    void move(float moveBy);
    void rotateCannon(float rotateBy);

    sf::RectangleShape getTankBody();
    sf::RectangleShape getTankCannon();

private:
    sf::Vector2f tankBodySize;
    sf::Vector2f tankCannonSize;
    sf::RectangleShape tankBody;
    sf::RectangleShape tankCannon;
    sf::Color color;
};