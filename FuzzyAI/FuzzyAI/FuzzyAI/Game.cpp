#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
    tiny = FuzzyTriangle(5, 7, 9, 11);
    small = FuzzyTrapezoid(6.5, 8.5, 10.5, 12.5, 14.5);
    moderate = FuzzyTrapezoid(8, 10, 12, 14, 16);
    large = FuzzyGrade(8, 25, 30);

    close = FuzzyTriangle(0, 200, 500, 800);
    medium = FuzzyTrapezoid(100, 400, 700, 1000, 1300);
    far = FuzzyGrade(200, 800, 1400);
    // close : Medium, High, High, High
    // Medium: Low, Low, Medium, High
    //    Far: Low, Low, Low, Medium

    lowRisk = FuzzyOR(FuzzyOR(FuzzyAND(medium, tiny),    FuzzyAND(medium, small)),    FuzzyAND(far, FuzzyNOT(large)));
    mediumRisk = FuzzyOR(FuzzyOR(FuzzyAND(close, tiny),    FuzzyAND(medium, moderate)),    FuzzyAND(far, large));
    highRisk = FuzzyOR(FuzzyAND(close, FuzzyNOT(tiny)),     FuzzyAND(medium, large));
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}



void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}


void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_window.display();
}

double Game::FuzzyAND(double A, double B)
{
	return std::min(A, B);
}

double Game::FuzzyOR(double A, double B)
{
	return std::max(A, B);
}

double Game::FuzzyNOT(double A)
{
	return 1.0 - A;
}

double Game::FuzzyTrapezoid(double v, double x0, double x1, double x2, double x3)
{
    double result = 0;
    double x = v;

    if ((x <= x0) || (x >= x3))
    {
        result = 0.0;
    }
    else if ((x >= x1) && (x <= x2))
    {
        result = 1.0;
    }
    else if ((x > x0) && (x < x1))
    {
        result = ((x - x0) / (x1 - x0));
    }
    else
    {
        result = ((x3 - x) / (x3 - x2));
    }
    return 0.0;
}

double Game::FuzzyGrade(double value, double x0, double x1)
{
    double result = 0;
    double x = value;

    if (x <= x0)
    {
        result = 0;
    }
    else if (x > x1)
    {
        result = 1;
    }
    else
    {
        result = ((x - x0) / (x1 - x0));
    }
    return result;
}

double Game::FuzzyTriangle(double value, double x0, double x1, double x2)
{
    double result = 0;
    double x = value;

    if ((x <= x0) || (x >= x2))
    {
        result = 0;
    }
    else if (x == x1)
    {
        result = 1;
    }
    else if ((x > x0) && (x < x1))
    {
        result = ((x - x0) / (x1 - x0));
    }
    else
    {
        result = ((x2 - x) / (x2 - x1));
    }
    return result;
}