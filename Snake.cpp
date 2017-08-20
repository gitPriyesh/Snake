// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "Food.h"
#include <iostream>
#include <sstream>
#include <unordered_map>



int main()
{
	//Seeding the random number generator once
	srand(time(NULL));
	
	//Mapping game speed to levels accordingly
	std::unordered_map < uint8_t,unsigned short > um_level;
	for (int i = 1,  j = 9; i < 10; i++, j--)
	{
		um_level[i] = j * 100;
	}

	uint8_t currentLevel = 1;

	sf::VideoMode vm(750,430);

	sf::RenderWindow window(vm, "SFML SNAKE", sf::Style::Titlebar | sf::Style::Close);

	//Player creation
	Player snake;
	snake.createPlayer();
	
	//Background
	sf::Texture textureBackground;
	textureBackground.loadFromFile("images/background.png");

	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0.f, 0.f);

	//Food creation
	Food food;
	food.spawn(&snake);

	//Setting up a clock
	sf::Clock clock;
	clock.restart();

	//Setting up message and score texts
	sf::Font msgFont;
	msgFont.loadFromFile("fonts/emulogic.ttf");

	sf::Text msgText;
	msgText.setFont(msgFont);
	msgText.setFillColor({ 27,27,27 });
	msgText.setCharacterSize(18);
	msgText.setString("Press any 1 to 9 key from\nnumpad to choose the level");

	sf::FloatRect rect = msgText.getLocalBounds();
	msgText.setOrigin((rect.width + rect.left) / 2, (rect.height + rect.top) / 2);
	msgText.setPosition(380, 180);

	unsigned short score = 0;

	sf::Text scoreText;
	scoreText.setFont(msgFont);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setCharacterSize(20);
	scoreText.setString("score = 0");
	scoreText.setPosition(280, 400);

	sf::Text retryText;
	retryText.setFont(msgFont);
	retryText.setFillColor({ 27, 27, 27 });
	retryText.setCharacterSize(20);
	retryText.setString("Press 'space' to retry");

	rect = retryText.getLocalBounds();
	retryText.setOrigin((rect.width + rect.left) / 2, (rect.height + rect.top) / 2);
	retryText.setPosition(375, 300);

	
	//Game state is paused in the start
	bool paused = true;

	//is Game over?
	bool gameOver = false;
	
	bool displayCountDown = false;

	sf::Vector2f lastBlockPos({ 0,0 });

	//Game loop
	while (window.isOpen())
	{
		//Time passed since clock restarted
		sf::Time dt = clock.getElapsedTime();
		
		//Event handling
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch(evnt.type) {
				case (sf::Event::Closed):
					window.close();
					break;

				case (sf::Event::KeyPressed):
					if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
					{
						//reset player
						snake.deletePlayer();
						snake.createPlayer();

						gameOver = false;
						displayCountDown = true;

						std::stringstream ss;
						ss << "score = " << score;
						
						scoreText.setString(ss.str());
						scoreText.setPosition(375, 410);
						scoreText.setFillColor(sf::Color::White);
					}
					break;
			}

			//Player choosing a level at the start of the game
			if(paused && evnt.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
				{
					currentLevel = 1;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
				{
					currentLevel = 2;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
				{
					currentLevel = 3;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
				{
					currentLevel = 4;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
				{
					currentLevel = 5;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
				{
					currentLevel = 6;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
				{
					currentLevel = 7;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
				{
					currentLevel = 8;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
				{
					currentLevel = 9;
				}
				else
				{
					break;
				}

				displayCountDown = true;
			}
		}
		// End event handling

		//Paused while counting down
		while (displayCountDown)
		{
			// Clock restarts after the level is chosen
			if (paused)
			{
				clock.restart();
				paused = false;
			}
			
			dt = clock.getElapsedTime();
			
			sf::Text countText;
			countText.setFont(msgFont);
			countText.setCharacterSize(30);
			countText.setFillColor(sf::Color::Black);

			std::stringstream ss;

			int i = 0;

			if (dt.asMilliseconds() < 1000){
				i = 3;
				ss << i;
			}
			else if (dt.asMilliseconds() > 1000 && dt.asMilliseconds() < 2000){
				i = 2;
				ss << i;
			}
			else if (dt.asMilliseconds() > 2000 && dt.asMilliseconds() < 3000){
				i = 1;
				ss << i;
			}
			else if (dt.asMilliseconds() > 3000 && dt.asMilliseconds() < 4000){
				ss << "GO";
			}
			else if (dt.asMilliseconds() > 4000){
				gameOver = false;
				displayCountDown = false;
			}

			countText.setString(ss.str());

			rect = countText.getLocalBounds();
			countText.setOrigin((rect.width + rect.left) / 2, (rect.height + rect.top) / 2);
			countText.setPosition(375, 195);
			countText.setFillColor({ 27,27,27 });

			window.clear();
			
			window.draw(spriteBackground);
			window.draw(countText);
			window.draw(scoreText);

			window.display();
		}

		//Deciding snake head direction by taking player input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.getDirection() != Direction::DOWN)
		{
			snake.setDirection(Direction::UP);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.getDirection() != Direction::UP)
		{
			snake.setDirection(Direction::DOWN);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.getDirection() != Direction::LEFT)
		{
			snake.setDirection(Direction::RIGHT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.getDirection() != Direction::RIGHT)
		{
			snake.setDirection(Direction::LEFT);
		}

		//Game play start
		if (!paused && !gameOver)
		{
			//Snake movement and speed according to the level chosen
			if (dt.asMilliseconds() > um_level[currentLevel])
			{
				snake.move();

				clock.restart();
			}
			//End snake movement direction and speed

			//Handling snake food intersection
			if (snake.getHeadPosition().x == food.getPosition().x &&
				snake.getHeadPosition().y == food.getPosition().y)
			{
				//Score up
				for (int i = 0; i < currentLevel; i++)
				{
					score++;
				}

				food.spawn(&snake);
				snake.addBlock();

				std::stringstream myStr;
				myStr << "score = " << score;
				scoreText.setString(myStr.str());
			}
			
			//Handling game over
			if (snake.isCollided())
			{
				clock.restart();
				
				paused = true;

				//Setting the position of last block to its previous position 
				snake.setLastBlockPosition(lastBlockPos);

				msgText.setString("GAME OVER");
				msgText.setCharacterSize(20);

				rect = msgText.getLocalBounds();
				msgText.setOrigin((rect.width + rect.left) / 2, (rect.height + rect.top) / 2);
				msgText.setPosition(375, 140);

				rect = scoreText.getLocalBounds();
				scoreText.setOrigin((rect.width + rect.left) / 2, (rect.height + rect.top) / 2);
				scoreText.setCharacterSize(20);
				scoreText.setPosition(375, 410);

				//A pause
				while (!gameOver)
				{
					dt = clock.getElapsedTime();
					if (dt.asMilliseconds() < 1500)
					{	
						snake.setFillColor({ 0,0,0,170 });
						
						window.clear();
						
						window.draw(spriteBackground);
						window.draw(food.getSquare());
						snake.drawTo(window);
						window.draw(scoreText);

						window.display();
					}
					else
					{
						gameOver = true;

						scoreText.setPosition(375, 170);
						scoreText.setFillColor({ 27,27,27 });

						score = 0;
					}
				}
			}
			else
			{
				//Capturing the position of last block while snake is not collided
				lastBlockPos = snake.getBlockPosition(snake.getSize()-1);
			}
			//End game over
		}
		//End play start

		window.clear();

		window.draw(spriteBackground);
		
		//Drawing at the start of the game
		if (paused && !gameOver)
		{
			window.draw(msgText);
			window.draw(scoreText);
			
		}
		
		//Drawing when the game is over
		else if (paused && gameOver)
		{
			window.draw(msgText);
			window.draw(scoreText);
			window.draw(retryText);
		}
		
		//Drawing during gameplay
		else
		{
			window.draw(food.getSquare());
			snake.drawTo(window);
			window.draw(scoreText);
		}

		window.display();
	}
	
	return 0;
}

