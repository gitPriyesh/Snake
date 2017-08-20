#pragma once
#ifndef _BLOCK_
#define _BLOCK_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Direction.h"
#include <vector>


class Block {
private:
	sf::RectangleShape m_square;

	Direction blockDirection;

public:
	Block();

	sf::RectangleShape getSquare();

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();

	void setDirection(Direction direction);
	Direction getDirection();

	void setFillColor(sf::Color color);
};

#endif // !_BLOCK_