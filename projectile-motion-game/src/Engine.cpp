#include "Engine.hpp"
#include <typeinfo>

// Init functions
void Engine::initVariables() {
    this->window = nullptr;
    this->endGame = false;

    this->rotateBy = 25.f;
    this->initAngle = 90.f;
    this->groundStart = 980.f;
    this->moveSpeed = 30.f;
}
void Engine::initWindow() {
    this->videoMode.height = 1080;
    this->videoMode.width = 1920;
    this->window = new sf::RenderWindow(this->videoMode, "SFML");
    this->window->setFramerateLimit(60);
}
void Engine::initView() {
    this->view.setSize(1920.f, 1080.f);
    this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
    this->viewSpeed = 50.f;
}
void Engine::initElems() {
    this->ground.setSize(sf::Vector2f(1920.f, 100.f));
    this->ground.setPosition(sf::Vector2f(0, this->groundStart));
    this->ground.setFillColor(sf::Color::White);

    Tank *tank1 = new Tank();
    tank1->setPosition(sf::Vector2f(500.f, this->groundStart-tank1->getTankBody().getSize().y));
    tank1->setColor(sf::Color::Green);

    this->tanks.push_back(tank1);
}

// Constructor
Engine::Engine() {
    this->initVariables();
    this->initWindow();
    this->initView();
    this->initElems();
} 
Engine::~Engine() {
    for (auto &tank : tanks) {
        delete tank;
    }
    delete this->window;
}

// Accessors
const bool Engine::running() const { return this->window->isOpen(); }
const bool Engine::getEndGame() const { return this->endGame; }

// Update Functions
void Engine::pollEvents() {
    while(this->window->pollEvent(this->ev)) {
        switch(this->ev.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}
void Engine::updateCamera() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {        // Left
        view.move(-viewSpeed * timeNow, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // Right
        view.move(viewSpeed * timeNow, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // Up
        view.move(0.f, -viewSpeed * timeNow);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // Down
        view.move(0.f, viewSpeed * timeNow);
    }
}
void Engine::playerInput() {
    std::cout << "init angle: " << this->initAngle << std::endl;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {  // Tank moves horizontally to right
        tanks[0]->move(this->moveSpeed*dt);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {  // Tank moves horizontally to left
        tanks[0]->move(-this->moveSpeed*dt);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {  // Cannon angle up
        tanks[0]->rotateCannon(-this->rotateBy * dt);
        this->initAngle += 25.f * dt;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // Cannon angle down
        tanks[0]->rotateCannon(this->rotateBy * dt);
        this->initAngle -= 25.f * dt;
    }

}
void Engine::updateObjs() {

}
void Engine::update() {
    this->pollEvents();

    // Update time
    this->dt = clock.restart().asSeconds();
    this->elapsed = clock.getElapsedTime().asSeconds();
    this->timeNow = elapsed;

    // std::cout << tanks[0]->getTankBody().getPosition().x << std::endl;
    tanks[0]->getTankBody().setFillColor(sf::Color::Green);

    if (this->endGame == false) {
        this->updateCamera();
        this->playerInput();
        this->updateObjs();
    }
}

// Render
void Engine::renderObjs(sf::RenderTarget& target) {
    for (auto &tank : this->tanks) {
        target.draw(tank->getTankBody());
        target.draw(tank->getTankCannon());
    }
    target.draw(this->ground);
}
void Engine::render() {
    this->window->clear();
    this->window->setView(view);

    // Draw game objects
    this->renderObjs(*this->window);
    this->window->setView(this->window->getDefaultView());

    this->window->display();
}
