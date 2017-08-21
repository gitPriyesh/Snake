#include "stdafx.h"
#include "Food.h"


Food::Food():m_square(sf::Vector2f (15.f,15.f))
{
	m_square.setFillColor({ 173,51,51 });
}

void Food::spawn(Player* snake)
{	
	sf::Vector2f factor{ static_cast<float>(rand() % 735) / SIZE, static_cast<float>(rand() % 375) / SIZE };

	sf::Vector2f position{ round(factor.x) * SIZE, round(factor.y) * SIZE };
	 
	m_position = position;

	//Logic for food spawn only on vacant space(not behind the snake)
	for (int i = 0; i < snake->getSize(); i++)
	{
		if (m_position == snake->getBlockPosition(i))
		{
			sf::Vector2f factor{ static_cast<float>(rand() % 735) / SIZE, static_cast<float>(rand() % 375) / SIZE };

			sf::Vector2f position{ round(factor.x) * SIZE, round(factor.y) * SIZE };

			m_position = position;
			
			//setting i = -1 here will again compare the food's position against snake's blocks position
			i = -1;
		}
	}

	m_square.setPosition(m_position);
}

sf::Vector2f Food::getPosition()
{
	return m_position;
}

sf::RectangleShape Food::getSquare()
{
	return m_square;
}
