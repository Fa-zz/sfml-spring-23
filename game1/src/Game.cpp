#include "Game.hpp"

// Private functions
void Game::initVariables() {
    this->window = nullptr;

    // Game logic
    this->points = 0;
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    //this->videoMode.getDesktopMode
    this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
    this->enemy.setPosition(sf::Vector2f(0.0f, 0.0f));
    this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

// Constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

// Destructor
Game::~Game() {
    delete this->window;
}

// Accessors
const bool Game::running() const {
    return this->window->isOpen();
}

// Functions

// Spawns enemies and sets their color and pos (both random), adds enemies to enemy vector
void Game::spawnEnemy() {
    // To spawn an enemy, 
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    this->enemy.setFillColor(sf::Color::Green);

    // Spawn an enemy
    this->enemies.push_back(this->enemy);

    // Remove an enemy at end of screen
}


void Game::pollEvents() {
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
void Game::updateMousePos() {
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

// Updates the enemy spawn timer and spawns enemies when the total amount of enemies is smaller than max. Moves enemies downwards, and removes at edge of screen
void Game::updateEnemies() {
    // Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {

        if(this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            // Spawn enemy and reset timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        } else {
            this->enemySpawnTimer += 1.f;
        }
    }

    //Move the enemies
    for (auto &e : this->enemies) {
        e.move(0.f, 3.f);
    }

}

void Game::update() {
    this->pollEvents();

    // Update mouse pos
    this->updateMousePos();

    this->updateEnemies();
}

void Game::renderEnemies() {
    //render all enemies
    for (auto &e : this->enemies) {
        this->window->draw(e);
    }
}

void Game::render() {
    this->window->clear();

    // Draw game objects
    this->renderEnemies();

    this->window->display();
}