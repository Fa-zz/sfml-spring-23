#include "Player.hpp"

// Initializer functions
void Player::initVariables() {

}

void Player::initShape() {
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(100.f, 100.f));

}

// Constructors and destructors
Player::Player() {
    this->initVariables();
    this->initShape();
}

Player::~Player() {

}

// Functions
// Update: Move the player
void Player::update() {
    
}

// Render: Draw the player
void Player::render(sf::RenderTarget* target) {
    target->draw(this->shape);
}