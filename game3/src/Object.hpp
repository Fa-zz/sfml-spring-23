#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Object {
public:
    // Default constructor
    Object();

    // Constructor with current pos parameterized
    Object(sf::Vector2f posCurrent);

    // Setter for object's position and visual
    void setPos(sf::Vector2f pos);
    // Setter for object's position
    void setPosObject(sf::Vector2f pos);
    // Setter for object's visual
    void setPosVisual(sf::Vector2f pos);

    // Getter for visual
    sf::CircleShape getVisual();

    // Applies verlet integration to object, and moves visual
    void updatePosition(float dt);

    // Adds a passed Vector2f value to acceleration
    void accelerate(sf::Vector2f acc);

private:
    sf::CircleShape visual;         // visual: Holds all visual info about object, including color, radius, position
    sf::Vector2f positionCurrent;   // positionCurrent: The current position the object holds
    sf::Vector2f positionOld;       // positionOld: The old position the object had
    sf::Vector2f acceleration;      // acceleration: The acceleration of the object

};