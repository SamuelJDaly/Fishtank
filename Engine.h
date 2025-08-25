#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "Fish.h"
#include "Util.h"

class Engine
{
private:
	//#### Data
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock engineClk;
	float dt;
	bool isRunning = true;

	std::vector<sf::Texture*> textures;

	sf::IntRect tankBounds = {0,0,1200,800};
	std::vector<Fish*> fish;
	std::vector<Fish> fictionary;


	//#### Init
	void initWindow();
	void initTextures();
	void initFictionary();
	void initTest();

public:
	//#### Constructors and Destructors
	Engine();
	~Engine();

	//#### Primary Functions
	void poll();
	void update();
	void draw();

	bool getRunning();
};

