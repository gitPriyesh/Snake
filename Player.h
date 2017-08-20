#pragma once
#ifndef _PLAYER_
#define _PLAYER_

#include <iostream>
#include <vector>
#include "Block.h"
#include <SFML/Graphics.hpp>


class Player
{
private:
	Block block;
	std::vector<Block> snake;
	
	sf::Vector2f m_Position;

	const uint8_t PX_PER_FRAME = 15;

	unsigned short size;

public:
	void createPlayer();

	void deletePlayer();

	bool isCollided();

	void addBlock();

	void drawTo(sf::RenderWindow &window);

	void setDirection(Direction direction);
	
	Direction getDirection();

	void move();

	void setHeadPosition(sf::Vector2f position);
	
	sf::Vector2f getHeadPosition();

	sf::Vector2f getBlockPosition(int i);

	void setLastBlockPosition(sf::Vector2f position);

	void setFillColor(sf::Color color);

	unsigned short getSize();
};

#endif // !_PLAYER_