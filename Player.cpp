#include "stdafx.h"
#include "Player.h"


void Player::createPlayer()
{
	for (int i = 0; i < 4; i++) {
		snake.push_back(block);
		snake[i].setPosition({ 195 - static_cast<float>(i * PX_PER_FRAME),195 });
	}
}

void Player::deletePlayer()
{
	snake.clear();
}

bool Player::isCollided()
{
	for (int i = 1; i < snake.size(); i++)
	{	
		if (snake[0].getPosition() == snake[i].getPosition() ||
			snake[0].getPosition().x > 735 || snake[0].getPosition().x < 0 ||
			snake[0].getPosition().y > 375 || snake[0].getPosition().y < 0)
		{
			for (int j = 1; j < snake.size(); j++)
			{
				snake[j - 1].setPosition(snake[j].getPosition());
			}
			return true;
		}
	}
	return false;
}

void Player::addBlock()
{
	snake.push_back(block);
	snake[snake.size() - 1].setPosition(snake[snake.size() - 2].getPosition());
}

void Player::drawTo(sf::RenderWindow &window)
{
	for (Block current : snake)
	{
		window.draw(current.getSquare());
	}
}

void Player::setDirection(Direction direction)
{
	snake[0].setDirection(direction);
}

Direction Player::getDirection()
{
	return snake[0].getDirection();
}

void Player::move()
{
	//Direction of the snake head and its movement
	switch (snake[0].getDirection())
	{
		case (Direction::RIGHT):
			snake[0].setPosition({ (snake[0].getPosition().x + PX_PER_FRAME), snake[0].getPosition().y });
			break;
		case (Direction::LEFT):
			snake[0].setPosition({ (snake[0].getPosition().x - PX_PER_FRAME), snake[0].getPosition().y });
			break;
		case (Direction::DOWN):
			snake[0].setPosition({ snake[0].getPosition().x, (snake[0].getPosition().y + PX_PER_FRAME) });
			break;
		case (Direction::UP):
			snake[0].setPosition({ snake[0].getPosition().x, (snake[0].getPosition().y - PX_PER_FRAME) });
			break;
	}
	
	for (int i = (snake.size() - 1); i > 0; i--)
	{
		//Setting the direction of the previous block to the current block
		snake[i].setDirection(snake[i - 1].getDirection());
	}

	for (int i = 1; i < snake.size(); i++)
	{
		switch (snake[i].getDirection())
		{
			case (Direction::RIGHT):
				snake[i].setPosition({ (snake[i - 1].getPosition().x - PX_PER_FRAME), snake[i - 1].getPosition().y });
				break;
			case (Direction::LEFT):
				snake[i].setPosition({ (snake[i - 1].getPosition().x + PX_PER_FRAME), snake[i - 1].getPosition().y });
				break;
			case (Direction::DOWN):
				snake[i].setPosition({ snake[i - 1].getPosition().x, (snake[i - 1].getPosition().y - PX_PER_FRAME) });
				break;
			case (Direction::UP):
				snake[i].setPosition({ snake[i - 1].getPosition().x, (snake[i - 1].getPosition().y + PX_PER_FRAME) });
				break;
		}
	}
}

void Player::setHeadPosition(sf::Vector2f position)
{
	snake[0].setPosition(position);
}

sf::Vector2f Player::getHeadPosition()
{
	return snake[0].getPosition();
}

sf::Vector2f Player::getBlockPosition(int i)
{
	return snake[i].getPosition();
}

void Player::setLastBlockPosition(sf::Vector2f position)
{
	snake[snake.size() - 1].setPosition(position);
}

void Player::setFillColor(sf::Color color)
{
	//Logic for filling 'color' in already created 'block' in every index of vector 'snake' 
	for (int i = 0; i < snake.size(); i++) {
		Block *b = &snake[i];
		b->setFillColor(color);
	}
}

unsigned short Player::getSize()
{
	return snake.size();
}
