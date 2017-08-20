#pragma once
#ifndef _FOOD_
#define _FOOD_

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Player.h"

class Food {
private:
	sf::RectangleShape m_square;
	
	sf::Vector2f m_position;

	const float SIZE{ 15.f };

public:
	Food();

	void spawn(Player* snake);
	
	sf::Vector2f getPosition();

	sf::RectangleShape getSquare();
};

#endif // !_FOOD_
