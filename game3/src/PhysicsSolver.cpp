#include "PhysicsSolver.hpp"

// Constructor
PhysicsSolver::PhysicsSolver() {
    this->gravity = sf::Vector2f{0.0f, 750.0f};
    this->currObject = nullptr;
}

// setCurrObj:
// Preconditions: 
// Postconditions: 
void PhysicsSolver::setCurrObj(Object object) {
    this->currObject = &object;
    std::cout << "setCurrObj successful" << std::endl;
    std::cout << (*currObject).getVisual().getPosition().x << std::endl;
}

// update: 
// Preconditions: 
// Postconditions: 
void PhysicsSolver::update(Object *object, float dt) {
    updatePositions(object, dt);
    applyGravity(object);

}

// updatePositions: 
// Preconditions: 
// Postconditions: 
void PhysicsSolver::updatePositions(Object *object, float dt) {
    object->updatePosition(dt);
}

// applyGravity: 
// Preconditions: 
// Postconditions: 
void PhysicsSolver::applyGravity(Object *object) {
    object->accelerate(gravity);
}

// applyConstraints: 
// Preconditions: 
// Postconditions: 
void PhysicsSolver::applyConstraints(Object *object) {

}