#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Object {
public:
    Object();

    Object(sf::Vector2f posCurrent);

    void setPos(sf::Vector2f pos);
    sf::CircleShape getVisual();

    void updatePosition(float dt);

    void accelerate(sf::Vector2f acc);

private:
    sf::CircleShape visual;
    sf::Vector2f positionCurrent;
    sf::Vector2f positionOld;
    sf::Vector2f acceleration;

};