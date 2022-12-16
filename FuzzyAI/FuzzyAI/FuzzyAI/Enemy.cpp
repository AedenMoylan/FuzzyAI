#include "Enemy.h"

void Enemy::init()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemyShape[i].setSize(sf::Vector2f(10, 10));
		enemyShape[i].setFillColor(sf::Color::Red);
		enemyShape[i].setPosition(200,200);
	}
}
