#include "Object.hpp"

// Constructor
Object::Object() {
    // Set position values for object
    this->positionCurrent = sf::Vector2f(0.f, 0.f);
    this->positionOld = sf::Vector2f(0.f, 0.f);

    // Set position values for object's visual
    this->visual.setPosition(0.f, 0.f);
    this->visual.setRadius(100.f);

    // Acceleration is set to zero
    this->acceleration = sf::Vector2f(0.f, 0.f);
}

// Parameterized constructor
Object::Object(sf::Vector2f posCurrent):positionCurrent(posCurrent), positionOld(posCurrent) {
    this->visual.setPosition(posCurrent);
    this->visual.setRadius(100.f);
}

//
void Object::setPos(sf::Vector2f pos) { 
    this->positionCurrent = pos;
    this->positionOld = pos;    
    this->visual.setPosition(pos);
}

// setPosObject: Setter for the position of an object
// Preconditions: Object exists
// Postconditions: Object has an updated position
void Object::setPosObject(sf::Vector2f pos) { 
    this->positionCurrent = pos;
    this->positionOld = pos;    
    this->visual.setPosition(pos);
}

// setPosVisual Setter for the position of an object's visual
// Preconditions: Object exists
// Postconditions: Visual has an updated position
void Object::setPosVisual(sf::Vector2f pos) {
    this->visual.setPosition(pos);
}

void Object::setSizeVisual(float radius) {
    this->visual.setRadius(radius);
}

// getVisual: Getter for visual of object
// Preconditions: Object exists
// Postconditions: None
sf::CircleShape Object::getVisual() {
    return this->visual;
}

// updatePosition: Performs verlet integration to update position of object given change in velocity, time, and acceleration.
// Visual also moves based on velocity 
// Preconditions: Object exists
// Postconditions: Object has a displacement in position if there is a change in acceleration
void Object::updatePosition(float dt) {
    std::cout << " At start, positionOld: " << this->positionOld.x << " " << this->positionOld.y << std::endl;
    std::cout << " At start, acceleration = " << this->acceleration.x << " " << this->acceleration.y << std::endl;
    const sf::Vector2f velocity = this->positionCurrent - this->positionOld;
    // Save current position
    this->positionOld = this-> positionCurrent;
    // Perform Verlect integration
    this->positionCurrent = this->positionCurrent + velocity + this->acceleration * dt * dt;

    // Moves the visual
    this->setPosVisual(positionCurrent);
    // Reset acceleration
    acceleration = {0.f, 0.f};

    std::cout << "Time: " << dt << " Velocity: " << velocity.x << " " << velocity.y << " positionCurrent: " << this->positionCurrent.x << " " << this->positionCurrent.y << " positionOld: " << this->positionOld.x << " " << this->positionOld.y << " accel: " << this->acceleration.x << " " << this->acceleration.y << std::endl;
}

// accelerate: Adds a passed-in Vector2f to the acceleration of an object
// Preconditions: 
// Postconditions: 
void Object::accelerate(sf::Vector2f acc) {
        this->acceleration += acc;
        std::cout << "Acceleration after addition: " << acceleration.x << " " << acceleration.y << std::endl;
    }
