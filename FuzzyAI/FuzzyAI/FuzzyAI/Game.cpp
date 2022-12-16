#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1800U, 1500U, 32U }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
    if (!font.loadFromFile("Roman SD.ttf"))
    {
        // error...
    }



    srand(time(NULL));

    player.init();
    enemy.init();
    callFuzzy();
    setText();
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
    if (sf::Keyboard::R == t_event.key.code)
    {
        callFuzzy();
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
    m_window.draw(player.playerShape);

    for (int i = 0; i < 50; i++)
    {
        m_window.draw(enemy.enemyShape[i]);
    }
    m_window.draw(tinyText);
    m_window.draw(smallText);
    m_window.draw(moderateText);
    m_window.draw(largeText);
    m_window.draw(closeText);
    m_window.draw(mediumText);
    m_window.draw(farText);
    m_window.draw(lowRiskText);
    m_window.draw(mediumRiskText);
    m_window.draw(highRiskText);
    m_window.draw(deploymentText);

    

	m_window.display();
	m_window.clear(sf::Color::Black);

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
    return result;
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

void Game::callFuzzy()
{


    numOfEnemies = rand() % 30 + 1;
    distance = rand() % 1000 + 200;

    tiny = FuzzyTriangle(numOfEnemies, 1, 3, 5);
    small = FuzzyTrapezoid(numOfEnemies, 4, 7, 10, 13);
    moderate = FuzzyTrapezoid(numOfEnemies, 12, 15, 19, 23);
    large = FuzzyGrade(numOfEnemies, 23, 27);

    close = FuzzyTriangle(distance, 200, 400, 600);
    medium = FuzzyTrapezoid(distance, 500, 700, 900, 1100);
    far = FuzzyGrade(distance, 1000, 1300);
    // close : Medium, High, High, High
    // Medium: Low, Low, Medium, High
    //    Far: Low, Low, Low, Medium

    lowRisk = FuzzyOR(FuzzyOR(FuzzyAND(medium, tiny), FuzzyAND(medium, small)), FuzzyAND(far, FuzzyNOT(large)));
    mediumRisk = FuzzyOR(FuzzyOR(FuzzyAND(close, tiny), FuzzyAND(medium, moderate)), FuzzyAND(far, large));
    highRisk = FuzzyOR(FuzzyAND(close, FuzzyNOT(tiny)), FuzzyAND(medium, large));

    deployment = (lowRisk * 10 + mediumRisk * 30 + highRisk * 50) / (lowRisk + mediumRisk + highRisk);

    setTextValues();
    for (int i = 0; i < 50; i++)
    {
        if (i < deployment)
        {
            enemy.enemyShape[i].setPosition((i * 20) + 300, distance);
        }
        else
        {
            enemy.enemyShape[i].setPosition(5000,5000);
        }

    }
}

void Game::setText()
{
    tinyText.setFont(font);
    smallText.setFont(font);
    moderateText.setFont(font);
    largeText.setFont(font);

    closeText.setFont(font);
    mediumText.setFont(font);
    farText.setFont(font);

    lowRiskText.setFont(font);
    mediumRiskText.setFont(font);
    highRiskText.setFont(font);

    deploymentText.setFont(font);

    tinyText.setCharacterSize(15);
    smallText.setCharacterSize(15);
    moderateText.setCharacterSize(15);
    largeText.setCharacterSize(15);

    closeText.setCharacterSize(15);
    mediumText.setCharacterSize(15);
    farText.setCharacterSize(15);

    lowRiskText.setCharacterSize(15);
    mediumRiskText.setCharacterSize(15);
    highRiskText.setCharacterSize(15);

    deploymentText.setCharacterSize(15);

    tinyText.setFillColor(sf::Color::White);
    smallText.setFillColor(sf::Color::White);
    moderateText.setFillColor(sf::Color::White);
    largeText.setFillColor(sf::Color::White);

    closeText.setFillColor(sf::Color::White);
    mediumText.setFillColor(sf::Color::White);
    farText.setFillColor(sf::Color::White);

    lowRiskText.setFillColor(sf::Color::White);
    mediumRiskText.setFillColor(sf::Color::White);
    highRiskText.setFillColor(sf::Color::White);

    deploymentText.setFillColor(sf::Color::White);


}

void Game::setTextValues()
{
    sf::String tinyString = "tiny: " + std::to_string(tiny);
    tinyText.setString(tinyString);
    tinyText.setPosition(100, 200);

    sf::String smallString = "small: " + std::to_string(small);
    smallText.setString(smallString);
    smallText.setPosition(100, 250);

    sf::String moderateString = "moderate: " + std::to_string(moderate);
    moderateText.setString(moderateString);
    moderateText.setPosition(100, 300);


    sf::String largeString = "large: " + std::to_string(large);
    largeText.setString(largeString);
    largeText.setPosition(100, 350);

    sf::String closeString = "close: " + std::to_string(close);
    closeText.setString(closeString);
    closeText.setPosition(100, 400);

    sf::String mediumString = "medium: " + std::to_string(medium);
    mediumText.setString(mediumString);
    mediumText.setPosition(100, 450);

    sf::String farString = "far: " + std::to_string(far);
    farText.setString(farString);
    farText.setPosition(100, 500);

    sf::String lowRiskString = "lowRisk: " + std::to_string(lowRisk);
    lowRiskText.setString(lowRiskString);
    lowRiskText.setPosition(100, 550);

    sf::String mediumRiskString = "mediumRisk: " + std::to_string(mediumRisk);
    mediumRiskText.setString(mediumRiskString);
    mediumRiskText.setPosition(100, 600);

    sf::String highRiskString = "highRisk: " + std::to_string(highRisk);
    highRiskText.setString(highRiskString);
    highRiskText.setPosition(100, 650);

    sf::String deploymentString = "deployment: " + std::to_string(deployment);
    deploymentText.setString(deploymentString);
    deploymentText.setPosition(1000, 100);
}
