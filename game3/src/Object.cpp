#include "Object.hpp"

Object::Object() {
    positionCurrent = sf::Vector2f(0.f, 0.f);
    visual.setPosition(0.f, 0.f);
    visual.setRadius(100.f);
}

Object::Object(sf::Vector2f posCurrent):positionCurrent(posCurrent) {
    visual.setPosition(posCurrent);
    visual.setRadius(100.f);
}

void Object::setPos(sf::Vector2f pos) { 
    positionCurrent = pos;    
    visual.setPosition(pos);
}

sf::CircleShape Object::getVisual() {
    return visual;
}

void Object::updatePosition(float dt) {
        const sf::Vector2f velocity = positionCurrent - positionOld;
        // Save current position
        positionOld = positionCurrent;
        // Perform Verlect integration
        positionCurrent = positionCurrent + velocity + acceleration * dt * dt;
        // Reset acceleration
        acceleration = {0.f, 0.f};
    }

void Object::accelerate(sf::Vector2f acc) {
        acceleration += acc;
    }
