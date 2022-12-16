#include "Player.h"

void Player::init()
{
	playerShape.setSize(sf::Vector2f(50,50));
	playerShape.setFillColor(sf::Color::Yellow);
	playerShape.setPosition(1800 / 2,  100);
}
