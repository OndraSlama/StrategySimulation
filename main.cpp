#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Base.h"
#include "Game.h"

Game game = Game();

//sf::ContextSettings settings;
//settings.antialiasingLevel = 8;
//sf::RenderWindow window(sf::VideoMode(800, 600), "SFML shapes", sf::Style::Default, settings);
sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Sim");
Vector mousePos;


void drawEverything(){
	//Colors
	sf::Color boardBackgroundColor = sf::Color(20, 20, 20);
	sf::Color boardOutlineColor = sf::Color(100, 100, 100);
	sf::Color ballColor = sf::Color::Yellow;
	sf::Color redGoalColor = sf::Color::Black;
	sf::Color blueGoalColor = sf::Color::Black;
	float outlineThickness = 5;

	//draw board
	Vector boardPos = b2.u2p(Vector(0, boardHeight / 2));
	sf::RectangleShape sfboard;
	sfboard.setFillColor(boardBackgroundColor);
	sfboard.setOutlineThickness(outlineThickness);
	sfboard.setOutlineColor(boardOutlineColor);
	sfboard.setSize({ b2.u2pScale(boardWidth), b2.u2pScale(boardHeight)});
	sfboard.setPosition(boardPos.x, boardPos.y);
	window.draw(sfboard);

	//draw red goal
	Vector goalPos = b2.u2p(Vector(0, goalSize/2));
	sf::RectangleShape sfgoalRed;
	sfgoalRed.setFillColor(redGoalColor);
	sfgoalRed.setSize({ outlineThickness, b2.u2pScale(goalSize)});
	sfgoalRed.setPosition(goalPos.x - outlineThickness, goalPos.y);
	window.draw(sfgoalRed);
	//draw red goal
	goalPos = b2.u2p(Vector(boardWidth, goalSize / 2));
	sf::RectangleShape sfgoalBlue;
	sfgoalBlue.setFillColor(blueGoalColor);
	sfgoalBlue.setSize({ outlineThickness, b2.u2pScale(goalSize) });
	sfgoalBlue.setPosition(goalPos.x, goalPos.y);
	window.draw(sfgoalBlue);

	//draw ball
	Vector ballPos = b2.w2p(game.ball.body->GetPosition());
	sf::CircleShape sfball;
	sfball.setRadius(b2.u2pScale(ballRadius));
	sfball.setFillColor(ballColor);
	sfball.setOrigin(b2.u2pScale(ballRadius), b2.u2pScale(ballRadius));
	//pos = b2.u2p(Vector(boardWidth/2, 0));
	sfball.setPosition(ballPos.x, ballPos.y);
	window.draw(sfball);

	////draw center 
	//sf::CircleShape sfCenter;
	//sfCenter.setRadius(b2.u2pScale(ballRadius));
	//sfCenter.setFillColor(sf::Color::White);
	//sfCenter.setOrigin(b2.u2pScale(ballRadius), b2.u2pScale(ballRadius));
	//pos = b2.u2p(Vector(boardWidth/2, 0));
	//sfCenter.setPosition(pos.x, pos.y);
	//window.draw(sfCenter);
}

int main(){
	std::cout << "Hello World!\n";
	game.ball.mousePos = &mousePos;

	//// determine field dimensions
	//float fieldWidthPxl = windowWidth * fillRatio;
	//float fieldHeightPxl = windowHeight * fillRatio;
	//if (fieldWidthPxl * fieldWidthPxl * (boardHeight / boardWidth) < (fieldHeightPxl * fieldHeightPxl * (boardWidth / boardHeight))){
	//	fieldHeightPxl = fieldWidthPxl * (boardHeight / boardWidth);
	//} else{
	//	fieldWidthPxl = fieldHeightPxl * (boardWidth / boardHeight);
	//}

	//b2.pixelScale = fieldWidthPxl / b2.u2wScale(boardWidth);
	//b2Vec2 temp = b2.p2w(Vector(windowWidth / 2 - fieldWidthPxl / 2, windowHeight / 2));
	//b2.unitsOffsetX = temp.x;
	////b2.unitsOffsetY = temp.y;
	//printf("%4.2f %4.2f \n", temp.x, temp.y);

	//Vector temp1 = Vector(1000, 2000);
	//Vector temp2 = b2.u2p(temp1);
	//printf("%4.2f %4.2f \n", temp1.x, temp1.y);
	//printf("%4.2f %4.2f \n", temp2.x, temp2.y);


	window.setFramerateLimit(FPS);
	sf::Event event;
	

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.	
	sf::Clock clock;

	while (window.isOpen()){
		mousePos.x = sf::Mouse::getPosition(window).x;
		mousePos.y = sf::Mouse::getPosition(window).y;

		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Key::Escape){
					window.close();
				} else if (event.key.code == sf::Keyboard::Key::Return){
					std::cin.get();
				}
			}
			//Right mouse button
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.key.code == sf::Mouse::Left){
					game.ball.BindToTarget();
				}
			}

			if (event.type == sf::Event::MouseButtonReleased){
				if (event.key.code == sf::Mouse::Left){
					game.ball.Unbind();
				}
			}
		}//end event testing

		

		window.clear();
		for (int i = 0; i < simulationFPS/FPS; i++){
			game.Update();
		}			

		std::cout << game.ball.velocity.x << "," << game.ball.velocity.y << '\n';
		//std::cout << velocity.x << "," << velocity.y << '\n';

		drawEverything();

		window.display();

		//Speed of ball
		//std::cout << sqrt(sim.ball->velocity.lengthSquared()) << "\n";

		//Keyboard control
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			for (int i = 0; i < 4; i++) sim.red[i].velocity.y = -8000;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			for (int i = 0; i < 4; i++) sim.red[i].velocity.y = 8000;
		} else{
			for (int i = 0; i < 4; i++) sim.red[i].velocity.y = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
			for (int i = 0; i < 4; i++) sim.red[i].angular_velocity = -8000;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			for (int i = 0; i < 4; i++) sim.red[i].angular_velocity = 8000;
		} else{
			for (int i = 0; i < 4; i++) sim.red[i].angular_velocity = 0;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			for (int i = 0; i < 4; i++) sim.blu[i].velocity.y = -8000;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			for (int i = 0; i < 4; i++) sim.blu[i].velocity.y = 8000;
		} else{
			for (int i = 0; i < 4; i++) sim.blu[i].velocity.y = 0;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			for (int i = 0; i < 4; i++) sim.blu[i].angular_velocity = -8000;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			for (int i = 0; i < 4; i++) sim.blu[i].angular_velocity = 8000;
		} else{
			for (int i = 0; i < 4; i++) sim.blu[i].angular_velocity = 0;
		}*/

		float currentFps = 1.f / clock.restart().asSeconds();
		if (currentFps < 0.9 * FPS){
			//std::cout << currentFps << '\n';
		}
	}//end game loop
}
