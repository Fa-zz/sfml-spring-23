#pragma once

#include "Object.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class PhysicsSolver {
public:
    // Constructor
    PhysicsSolver();

    // Setter for the currObject pointer
    void setCurrObj(Object object);

    // Calls all update and apply functions for the solver
    void update(Object *object, float dt);

    // Calls object's update position functions
    void updatePositions(Object *object, float dt);

    // Calls object's accelerate function, with gravity value passed as arg
    void applyGravity(Object *object);

    // Performs collision detection
    void applyConstraints(Object *object);

private:
    sf::Vector2f gravity;   // gravity: Amount by which object's velocity "decreases" in y direction
    Object* currObject;     // currObject: Pointer that points to the object that is currently being updated

};