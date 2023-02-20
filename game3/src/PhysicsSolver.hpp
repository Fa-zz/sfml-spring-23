#pragma once

#include "Object.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class PhysicsSolver {
public:
    PhysicsSolver();

    void setCurrObj(Object object);

    void update(Object object, float dt);

    void updatePositions(float dt);

    void applyGravity();

private:
    sf::Vector2f gravity;
    Object* currObject;

};