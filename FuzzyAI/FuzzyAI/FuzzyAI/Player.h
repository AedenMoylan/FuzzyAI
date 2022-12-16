#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	void init();
	void draw(sf::RenderWindow t_window);

	sf::RectangleShape playerShape;
private:

};

