#include <iostream>
#include <cmath>
#include <unistd.h>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Example 02", sf::Style::Default);
	window.setFramerateLimit(60);
    sf::Clock clock;
    sf::View view;
    view.setSize(1920.f, 1080.f);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);

    float viewSpeed = 200.f;
    float elapsed1;
    float initAngle = 48.37f;
    float initVel = 24.08f;
    float initVelY, initVelX;
    float gravity = 9.81f;
    float gravityInAction = 0.5;
    float maxHeight, timeToReachMaxHeight, distAtMaxHeight;
    float velYAfter = 0.f;

	sf::CircleShape shape(25.f);
    sf::Vector2f position = {0.f, 980.f};
    shape.setPosition(sf::Vector2f(position));

    initVelX = (initVel+100.f) * (cos( (initAngle * 3.1459)/180.f ));
    initVelY = (initVel+100.f) * (sin( (initAngle * 3.1459)/180.f ));
    std::cout << "initVelY: " << initVelY << " initVelX: " << initVelX << std::endl;
    maxHeight =  -(initVelY*initVelY) / (2*gravity);
    timeToReachMaxHeight = sqrtf((-2*maxHeight) / gravity);
    distAtMaxHeight = initVelX * timeToReachMaxHeight;
    std::cout << "timeToReachMaxHeight: " << timeToReachMaxHeight << std::endl;
    std::cout << "Max height: " << maxHeight << " Max range: " << distAtMaxHeight << std::endl;

	while (window.isOpen()) {
        elapsed1 = clock.getElapsedTime().asSeconds();
        float timeNow = elapsed1;
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Update
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {        // Left
            view.move(-viewSpeed * elapsed1, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // Right
            view.move(viewSpeed * elapsed1, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // Up
            view.move(0.f, -viewSpeed * elapsed1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // Down
            view.move(0.f, viewSpeed * elapsed1);
        }

        // std::cout << "Shape's bounds: Shape's x: " 

        if (shape.getPosition().y > maxHeight, shape.getPosition().x < distAtMaxHeight) {
            initVelY -= 1.5f;
            shape.move(initVelX*timeNow, -initVelY*timeNow);
        } else if (shape.getPosition().y < 980.f) {
            usleep(10000);
            velYAfter += 9.5f;
            // initVelY += gravityInAction;
            shape.move(initVelX*timeNow, velYAfter*timeNow);
            //shape.move(sf::Vector2f((initVelX*timeNow), (initVelY*timeNow + (9.81f)*(timeNow)*(timeNow))));
        }

        // if (position.y <= -100.f) {
        //     position.x = 100.f + (initVelX)*(timeNow);
        //     position.y = -100.f + ((initVelY)*(timeNow)) + ((-9.81f)*(timeNow)*(timeNow));
        //     std::cout << "position.x: " << position.x << " position.y: " << position.y << std::endl;
        //     shape.setPosition(sf::Vector2f(position.x, position.y));
        // }
        // position.x = (initVelX)*(timeNow);
        // position.y = 1080.f + ((initVelY)*(timeNow)) + ((+9.81f)*(timeNow)*(timeNow));
        // std::cout << "position.x: " << position.x << " position.y: " << position.y << std::endl;

        // shape.move(sf::Vector2f((initVelX*timeNow), (initVelY*timeNow + (9.81f)*(timeNow)*(timeNow))));

		//Draw
		window.clear(sf::Color::Red);

		//Render
		window.draw(shape);
        window.setView(view);

		window.display();
	}

	return 0;
}