#include "Object.hpp"

Object::Object() {
    this->positionCurrent = sf::Vector2f(0.f, 0.f);
    this->positionOld = sf::Vector2f(0.f, 0.f);

    this->visual.setPosition(0.f, 0.f);
    this->visual.setRadius(100.f);

    this->acceleration = sf::Vector2f(0.f, 0.f);
}

Object::Object(sf::Vector2f posCurrent):positionCurrent(posCurrent), positionOld(posCurrent) {
    this->visual.setPosition(posCurrent);
    this->visual.setRadius(100.f);
}

void Object::setPos(sf::Vector2f pos) { 
    this->positionCurrent = pos;
    this->positionOld = pos;    
    this->visual.setPosition(pos);
}

sf::CircleShape Object::getVisual() {
    return this->visual;
}

void Object::updatePosition(float dt) {
    std::cout << " At start, positionOld: " << this->positionOld.x << " " << this->positionOld.y << std::endl;
    std::cout << " At start, acceleration = " << this->acceleration.x << " " << this->acceleration.y << std::endl;
    const sf::Vector2f velocity = this->positionCurrent - this->positionOld;
    // Save current position
    this->positionOld =this-> positionCurrent;
    // Perform Verlect integration
    this->positionCurrent = this->positionCurrent + velocity + this->acceleration * dt * dt;
    // Reset acceleration
    //acceleration = {0.f, 0.f};

    std::cout << "Velocity: " << velocity.x << " " << velocity.y << " positionCurrent: " << this->positionCurrent.x << " " << this->positionCurrent.y << " positionOld: " << this->positionOld.x << " " << this->positionOld.y << " accel: " << this->acceleration.x << " " << this->acceleration.y << std::endl;
}

void Object::accelerate(sf::Vector2f acc) {
        this->acceleration += acc;
        std::cout << "Acceleration after addition: " << acceleration.x << " " << acceleration.y << std::endl;
    }
