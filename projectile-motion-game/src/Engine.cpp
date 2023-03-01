#include "Engine.hpp"

// Init functions
void Engine::initVariables() {
    this->window = nullptr;
    this->endGame = false;
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
    this->viewSpeed = 200.f;
}
void Engine::initElems() {

}

// Constructor
Engine::Engine() {
    this->initVariables();
    this->initWindow();
    this->initView();
    this->initElems();
} 
Engine::~Engine() {
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
void Engine::playerInput() {

}
void Engine::updateObjs() {

}
void Engine::update() {
    this->pollEvents();

    // Update time
    elapsed = clock.getElapsedTime().asSeconds();
    float timeNow = elapsed;

    if (this->endGame == false) {
        this->updateCamera();
        this->playerInput();
        this->updateObjs();
    }
}

// Render
void Engine::renderObjs(sf::RenderTarget& target) {

}
void Engine::render() {
    this->window->clear();
    this->window->setView(view);

    // Draw game objects
    this->renderObjs(*this->window);
    this->window->setView(this->window->getDefaultView());

    this->window->display();
}
