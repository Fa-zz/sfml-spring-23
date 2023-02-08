#include "Game.hpp"

// Private functions
void Game::initVariables() {
    this->window = nullptr;

    // Game logic
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;
}

void Game::initWindow() {
    // this->videoMode.height = 600;
    // this->videoMode.width = 800;
    this->videoMode.height = 1000;
    this->videoMode.width = 1000;

    //this->videoMode.getDesktopMode
    this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initFonts() {
    if (!(this->fontDosisLight.loadFromFile("fonts/Dosis-Light.ttf"))) {
        std::cout << "ERROR::GAME::INITFONTS: Failed to load fonts!" << std::endl;
    }
}

void Game::initText() {
    this->uiText.setFont(this->fontDosisLight);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("HELLO WORLD");
}

void Game::initEnemies() {
    this->enemy.setPosition(sf::Vector2f(0.0f, 0.0f));
    this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
    //this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);
}

// Constructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

// Destructor
Game::~Game() {
    delete this->window;
}

// Accessors
const bool Game::running() const { return this->window->isOpen(); }
const bool Game::getEndGame() const { return this->endGame; }

// Functions

// Spawns enemies and sets types + colors. Pos is random. Adds enemies to enemy vector
void Game::spawnEnemy() {
    // To spawn an enemy, 
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

    // Spawn an enemy
    this->enemies.push_back(this->enemy);

    // Randomize enemy types
    int type = rand() % 5;
    switch (type) {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.0f, 10.0f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.0f, 30.0f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.0f, 50.0f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.0f, 70.0f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
        this->enemy.setFillColor(sf::Color::Green);
        break;

    default:
        break;
    }

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
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

// Updates the enemy spawn timer and spawns enemies when the total amount of enemies is smaller than max. Moves enemies downwards, and removes at edge of screen
void Game::updateEnemies() {
    // Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}
    //Moving and updating the enemies
    for (int i = 0; i < this->enemies.size(); i++) {
        bool deleted = false;

        this->enemies[i].move(0.f, 5.f);

        if (this->enemies[i].getPosition().y > this->window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }

    }

        // If enemy is clicked upon, delete
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            if (this->mouseHeld == false) {
                mouseHeld = true;
                bool deleted = false;
                for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
                    if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {

                        // Gain points
                        if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                            this->points += 10;
                        else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                            this->points += 7;
                        else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                            this->points += 5;
                        else if (this->enemies[i].getFillColor() == sf::Color::Red)
                            this->points += 3;
                        else if (this->enemies[i].getFillColor() == sf::Color::Green)
                            this->points += 1;


                        // Delete the enemy
                        deleted = true;
                        this->enemies.erase(this->enemies.begin() + i);

                    }
                }
            } 

        } else {
            this->mouseHeld = false;
        }
    
}

void Game::updateText() {
    std::stringstream ss;
    ss << "Points: " << this->points << "\n" << "Health: " << this->health;
    this->uiText.setString(ss.str());
}

void Game::update() {
    this->pollEvents();

    if (this->endGame == false) {
        this->updateMousePos();
        this->updateText();
        this->updateEnemies();
    }

    // end game condition
    if (this->health <= 0)
        this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target) {
    //render all enemies
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

void Game::render() {
    this->window->clear();

    // Draw game objects
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}