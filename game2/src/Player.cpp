#include "Player.hpp"

// Initializer functions
void Player::initVariables() {
    this->movementSpeed = 10.f;
}

void Player::initShape() {
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(100.f, 100.f));

}

// Constructors and destructors
Player::Player(float x, float y) {
    this->shape.setPosition(x, y);
    this->initVariables();
    this->initShape();
}

Player::~Player() {

}

// Functions

void Player::updateInput() {
    // Keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {      // Left 
        this->shape.move(-this->movementSpeed, 0.f);
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // Right
        this->shape.move(this->movementSpeed, 0.f);
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {      // Up
        this->shape.move(0.f, -this->movementSpeed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // Down
        this->shape.move(0.f, this->movementSpeed);
    }
}


// Update: Move the player
void Player::update(sf::RenderTarget* target) {
    // Window bounds collision

    this->updateInput();

}

// Render: Draw the player
void Player::render(sf::RenderTarget* target) {
    target->draw(this->shape);
}