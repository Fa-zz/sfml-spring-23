#include "PhysicsSolver.hpp"

// Constructor
PhysicsSolver::PhysicsSolver() {
    this->gravityYBaseline = -1000.0f;
    this->gravity = sf::Vector2f{0.0f, gravityYBaseline};
    this->currObject = nullptr;
}

// setCurrObj: Sets the currObject pointer to point to an object
// Preconditions: An object exists
// Postconditions: currObject is now set to that object
void PhysicsSolver::setCurrObj(Object object) {
    this->currObject = &object;
}

// update: Calls update functions: updatePosition, applyGravity, which update a passed in object based on time
// Preconditions: Object and change in time exists
// Postconditions: Update functions are called
void PhysicsSolver::update(Object *object, float dt) {
    updatePositions(object, dt);
    applyGravity(object);

}

// updatePositions: Applies object's verlet integration function on object
// Preconditions: Object exists, change in time exists, solver update function called
// Postconditions: There is change in velocity and displacement
void PhysicsSolver::updatePositions(Object *object, float dt) {
    object->updatePosition(dt);
}

// applyGravity: Object is accelerated by solver's gravity vector
// Preconditions: Object exists
// Postconditions: Object's acceleration has solver's gravity vector added to it
void PhysicsSolver::applyGravity(Object *object) {
    object->accelerate(gravity);
}

// Launch: Calculates angleLaunch, launchVelocityInitial, launchVelocityX, launchVelocityY
// Preconditions: 
// Postconditions: 
// void PhysicsSolver::Launch() {

// }

// applyConstraints: Collision detection
// Preconditions: Object and other structures (walls, ground, etc) exist and collision can be detected between them
// Postconditions: 
void PhysicsSolver::applyConstraints(Object *object) {

}