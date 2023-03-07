#include "Engine.hpp"
#include <typeinfo>

// Init functions
void Engine::initVariables() {
    this->window = nullptr;
    this->endGame = false;

    this->groundStart = 980.f;
    this->moveSpeed = 100.f;

    this->initAngle = 90.f;
    this->rotateBy = 25.f;
    this->chargedUp = false;
    this->initVel = 0.f;
    this->projectileInAir = false;
    this->gravity = 9.81f;
    this->afterVelY = 0.f;

    accumulator = 0;
    timestep = 1.0f / 60.0f;

    std::vector<Tank*> tanks;
    std::vector<sf::CircleShape*> projectiles;

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
    tank1->setPosition(sf::Vector2f(0.f, this->groundStart-tank1->getTankBody().getSize().y));
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
    // std::cout << "angle: " << this->initAngle << std::endl;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {  // Tank moves horizontally to right
        tanks[0]->move(this->moveSpeed*dt);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {  // Tank moves horizontally to left
        tanks[0]->move(-this->moveSpeed*dt);
    } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {  // Cannon angle up
        tanks[0]->rotateCannon(-this->rotateBy * dt);
        this->initAngle += rotateBy * dt;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // Cannon angle down
        tanks[0]->rotateCannon(this->rotateBy * dt);
        this->initAngle -= rotateBy * dt;
    }

    // Cannon power up while player holds down space
    while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->initVel += 0.001f;
        std::cout << "this->initVel:" << this->initVel << std::endl;
        this->chargedUp = true;
    }

    // If cannon is powered up, prepare to launch projectile
    if (chargedUp && !(projectileInAir)) {

        /*
        Set pointer to null
        Reset variables
        maxHeight += projectiles[0]->getPosition().y
        distAtMaxHeight += projectiles[0]->getPosition().x
        */

        // sf::CircleShape *projectile = nullptr;
        this->maxHeight = 0;
        this->distAtMaxHeight = 0;
        this->timeToReachMaxHeight = 0;

        initVelX = (initVel) * (cos( (initAngle * 3.1459)/180.f ));
        initVelY = (initVel) * (sin( (initAngle * 3.1459)/180.f ));

        if (initAngle >= 90.f)
            initVelX -= initVelX - initVelX;

        std::cout << "initVelY: " << initVelY << " initVelX: " << initVelX << std::endl;
        maxHeight =  -(initVelY*initVelY) / (2*gravity);
        maxHeight -= this->tanks[0]->getTankCannon().getPosition().y;
        timeToReachMaxHeight = sqrtf((-2*maxHeight) / gravity);
        distAtMaxHeight = initVelX * timeToReachMaxHeight;
        distAtMaxHeight += this->tanks[0]->getTankCannon().getPosition().x;
        std::cout << "timeToReachMaxHeight: " << timeToReachMaxHeight << std::endl;
        std::cout << "Max height: " << maxHeight << " Max range: " << distAtMaxHeight << std::endl;

        projectile = new sf::CircleShape(5.f);
        std::cout << "Projectile pointer" << std::endl;
        this->projectiles.push_back(projectile);
        // projectile->setRadius(5.f);
        sf::Vector2f projectileLocation = sf::Vector2f((this->tanks[0]->getTankCannon().getPosition().x + (this->tanks[0]->getTankCannon().getSize().x-((this->tanks[0]->getTankCannon().getSize().x)/2.f))), (this->tanks[0]->getTankCannon().getPosition().y - this->tanks[0]->getTankCannon().getSize().y)); 
        std::cout << "Projectile start y: " << this->tanks[0]->getTankCannon().getPosition().y - this->tanks[0]->getTankCannon().getSize().y << std::endl;
        std::cout << "Projectile start x: " << (this->tanks[0]->getTankCannon().getPosition().x + (this->tanks[0]->getTankCannon().getSize().x-((this->tanks[0]->getTankCannon().getSize().x)/2.f))) << std::endl;
        projectile->setPosition(projectileLocation);

        chargedUp = false;
        this->projectileInAir = true;
    }

}
void Engine::updateObjs() {
    if (projectileInAir) {
        std::cout << "Projectile y: " << projectiles[0]->getPosition().y << std::endl;
        std::cout << "Projectile X: " << projectiles[0]->getPosition().x << std::endl;
        
        bool conditionToReachMaxHeight;
        bool conditionToFallBackDown = projectiles[0]->getPosition().y < 980.f;
        bool smoothPeak = false;
        int sleepFor = 10000;
        float initVelXOffset = 3.f;
        float initVelYIncrementBy = 1.0f;
        float afterVelYIncrementBy = 9.5f;

        if (initAngle <= 85.f) { // Cannon shoots to the right
            conditionToReachMaxHeight = projectiles[0]->getPosition().y > maxHeight && projectiles[0]->getPosition().x < distAtMaxHeight;
        } else if (initAngle >= 95.f) { // Cannon shoots to the left
            conditionToReachMaxHeight = projectiles[0]->getPosition().y > maxHeight && projectiles[0]->getPosition().x > distAtMaxHeight;
        } else if (initAngle >= 85.f && initAngle <= 95.f) {  // Cannon is shooting upwards
            // pass
        }
        
        if (conditionToReachMaxHeight) {
            // initVelY -= initVelYIncrementBy;
            // projectiles[0]->move(10.f+initVelX*dt, -initVelY);
            sf::Vector2f positionNow = projectiles[0]->getPosition() + sf::Vector2f(initVelX, -initVelY);
            projectiles[0]->setPosition(0.999f*positionNow);
            smoothPeak = true;
        } else if (conditionToFallBackDown) {
            usleep(sleepFor);
            // initVelY *= dt;
            // initVelX *= dt;
            // afterVelY += afterVelYIncrementBy;
            // projectiles[0]->move(10.f+initVelX*dt, afterVelY);

            sf::Vector2f positionNow = projectiles[0]->getPosition() + sf::Vector2f(initVelX, initVelY);
            projectiles[0]->setPosition(0.999f*positionNow);

        }

        if (projectiles[0]->getPosition().y >= this->groundStart) {
            delete projectiles[0];
            projectiles.pop_back();
            projectile = nullptr;
            std::cout << "Projectile deleted" << std::endl;
            this->projectileInAir = false;
            this->initVel = 0;
            this->initVelX = 0;
            this->initVelY = 0;
            this->afterVelY = 0;
        }
    }
}
void Engine::update() {
    this->pollEvents();

    // Update time
    this->dt = clock.restart().asSeconds();
    // this->elapsed = clock.getElapsedTime().asSeconds();
    // this->timeNow = elapsed;
    accumulator += clock.restart().asSeconds();
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

    if (projectileInAir) {
        for (auto &projectile : this->projectiles) {
            target.draw(*projectile);
        }
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
