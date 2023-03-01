#include "Tank.hpp"
#include <iostream>

// Constructor
Tank::Tank() {
    this->tankBodySize.x = 100.f;
    this->tankBodySize.y = 50.f;
    this->tankCannonSize.x = 25.f;
    this->tankCannonSize.y = 75.f;

    this->tankBody.setSize(sf::Vector2f(this->tankBodySize.x, this->tankBodySize.y));
    this->tankCannon.setSize(sf::Vector2f(this->tankCannonSize.x, this->tankCannonSize.y));
}

// Destructor
Tank::~Tank() {

}

void Tank::setPosition(sf::Vector2f tankPosition) {
    this->tankBody.setPosition(tankPosition);
    // std::cout << "tankBody get position: " << this->tankBody.getPosition().x << std::endl;
    // std::cout << "endPointX : " << this->tankBody.getPosition().x + this->tankBody.getSize().x << std::endl;
    // float endpointX = this->tankBody.getPosition().x + this->tankBody.getSize().x;
    // float tankBodySpace = endpointX - this->tankBody.getPosition().x;
    // std::cout << "tankBodySpace : " << endpointX - this->tankBody.getPosition().x << std::endl;
    // // float midpointX = endpointX / 2.f;
    // float finalPointX = tankBodySpace / 2.f;
    float finalPointX = (this->tankBody.getPosition().x + this->tankBody.getSize().x) - (this->tankBody.getSize().x / 2.f);
    std::cout << this->tankBody.getPosition().x + this->tankBody.getSize().x << std::endl;
    std::cout << "finalPointX: " << finalPointX << std::endl;
    this->tankCannon.setPosition(sf::Vector2f(finalPointX-(this->tankCannonSize.x / 2.f), tankPosition.y-this->tankCannonSize.y));
    // this->tankCannon.setPosition(this->tankBodySize / 2.f);
}

void Tank::setColor(sf::Color color) {
    this->tankBody.setFillColor(color);
    this->tankCannon.setFillColor(color);
}

sf::RectangleShape Tank::getTankBody() { return tankBody; }
sf::RectangleShape Tank::getTankCannon() { return tankCannon; }
