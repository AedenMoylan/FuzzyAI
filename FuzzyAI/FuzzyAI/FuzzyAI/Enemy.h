#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class Enemy
{
public:
	void init();

	static const int MAX_ENEMIES = 50;
	sf::RectangleShape enemyShape[MAX_ENEMIES];

	
private:

};

