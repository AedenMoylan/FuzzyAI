#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>

class Game
{
public:
	Game();
	~Game();

	void run();

private:

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

	sf::RenderWindow m_window;
	bool m_exitGame;

};

#endif 
