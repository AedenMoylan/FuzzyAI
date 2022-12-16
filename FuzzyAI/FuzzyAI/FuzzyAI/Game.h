#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <string.h>

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	Player player;
	Enemy enemy;

	double numOfEnemies;
	double distance;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	double FuzzyAND(double A, double B);
	double FuzzyOR(double A, double B);
	double FuzzyNOT(double A);
	double FuzzyTrapezoid(double v, double x0, double x1, double x2, double x3);
	double FuzzyGrade(double value, double x0, double x1);
	double FuzzyTriangle(double value, double x0, double x1, double x2);

	void callFuzzy();

	void setText();
	void setTextValues();


	double tiny;
	double small;
	double moderate;
	double large;

	double close;
	double medium;
	double far;

	double highRisk;
	double mediumRisk;
	double lowRisk;

	double deployment;

	sf::Font font;

	sf::Text defuzzText;

	sf::Text tinyText;
	sf::Text smallText;
	sf::Text moderateText;
	sf::Text largeText;

	sf::Text closeText;
	sf::Text mediumText;
	sf::Text farText;

	sf::Text lowRiskText;
	sf::Text mediumRiskText;
	sf::Text highRiskText;

	sf::Text deploymentText;

	sf::RenderWindow m_window;
	bool m_exitGame;

};

#endif 
