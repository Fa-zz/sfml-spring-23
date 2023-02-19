#include "Engine.hpp"

// Private functions
void Engine::initVariables() {
    this->window = nullptr;
    this->gridSizeF = 100.f;
    gridSizeU = static_cast<unsigned>(gridSizeF);

    // Game logic
    this->gravity = 9.81f;
    this->endGame = false;
    this->mouseHeld = false;
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
    viewSpeed = 200.f;
}

void Engine::initObjs() {
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(sf::Color::Magenta);
    this->ground.setSize(sf::Vector2f(1920.f, 100.f));
    this->ground.setPosition(sf::Vector2f(0, 980.0f));
}

// Constructor
Engine::Engine() {
    this->initVariables();
    this->initWindow();
    this->initView();
    this->initObjs();
}

// Destructor
Engine::~Engine() {
    delete this->window;
}

// Accessors
const bool Engine::running() const { return this->window->isOpen(); }
const bool Engine::getEndGame() const { return this->endGame; }

// Update functions
void Engine::pollEvents() {
    // Event polling
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

// Updates the mouse positon
void Engine::updateMousePos() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Engine::updateCamera() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {        // Left
    view.move(-viewSpeed * dt, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // Right
        view.move(viewSpeed * dt, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // Up
        view.move(0.f, -viewSpeed * dt);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // Down
        view.move(0.f, viewSpeed * dt);
    }
    std::cout << shape.getPosition().y << std::endl;
}

void Engine::updateObjs() {
    if (!shape.getGlobalBounds().intersects(ground.getGlobalBounds())) {
        shape.move(0.f, gravity);
    }
}

void Engine::update() {
    // update dt
    dt = dtClock.restart().asSeconds();
    this->pollEvents();

    if (this->endGame == false) {
        this->updateMousePos();
        this->updateCamera();
        this->updateObjs();
    }
}

void Engine::renderObjs(sf::RenderTarget& target) {
    target.draw(shape);
    target.draw(ground);
}

void Engine::render() {
    this->window->clear();
    this->window->setView(view);

    // Draw game objects
    this->renderObjs(*this->window);
    this->window->setView(this->window->getDefaultView());

    this->window->display();
}