#include "stdafx.h"
#include "Block.h"

Block::Block() : m_square({ 14.f,14.f })
{
	blockDirection = Direction::RIGHT;
	m_square.setFillColor({ 27,27,27 });
}

sf::RectangleShape Block::getSquare()
{
	return m_square;
}

void Block::setPosition(sf::Vector2f position)
{
	m_square.setPosition(position);
}

sf::Vector2f Block::getPosition()
{
	return m_square.getPosition();
}

void Block::setDirection(Direction direction)
{
	blockDirection = direction;
}

Direction Block::getDirection()
{
	return blockDirection;
}

void Block::setFillColor(sf::Color color)
{
	m_square.setFillColor(color);
}






