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

    void update(Object *object, float dt);

    void updatePositions(Object *object, float dt);

    void applyGravity(Object *object);

private:
    sf::Vector2f gravity;
    Object* currObject;

};