#include "PhysicsSolver.hpp"

PhysicsSolver::PhysicsSolver() {
    this->gravity = sf::Vector2f{0.0f, 1000.0f};
    this->currObject = nullptr;
}

void PhysicsSolver::setCurrObj(Object object) {
    this->currObject = &object;
    std::cout << "setCurrObj successful" << std::endl;
    std::cout << (*currObject).getVisual().getPosition().x << std::endl;
}

void PhysicsSolver::update(Object *object, float dt) {
    //std::cout << (*currObject).getVisual().getPosition().x << std::endl;
    updatePositions(object, dt);
    applyGravity(object);

}

void PhysicsSolver::updatePositions(Object *object, float dt) {
    // std::cout << currObject->getVisual().getPosition().y << std::endl;
    // for each object, call updatePosition(dt)
    object->updatePosition(dt);
}

void PhysicsSolver::applyGravity(Object *object) {
    // for each object, call accelerate(gravity)
    object->accelerate(gravity);
}