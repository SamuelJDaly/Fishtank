#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Util.h"


class Fish
{
private:
	//### Data
	
	//General
	sf::Sprite sprite;
	sf::Texture* texture;
	sf::IntRect bounds = { 0,0,1000,1000 };

	//Personality
	int type = 0;
	sf::Color color = sf::Color::White;
	float scale = 1;
	float speed = 10; //px / s
	std::string name = "White Defaultfish";

	//Behavior
	float decisionTimer = 0;
	float decisionThreshold = 5;
	sf::Vector2f targetPos = {0,0};
	float targetDist = 0;
	float targetRange = 40;
	float targetAngle = 0;
	float bobTimer = 0;
	float bobThreshold = 1;
	int bobDirection = -1;
	float hunger = 0; // [0-100] chance of trying to eat
	float hungerRate = 1; //How much hunger increases in a second
	bool goalChange = 0;
	int goal = 0; //idle, move, flee, eat

	//Debug
	bool printVerbose = 0;
	bool drawVerbose = 0;
	sf::Vertex targLine[2];


	//### Util

public:
	//### Constructor and Destructor
	Fish();
	~Fish();

	//### Primary Functions
	void update(float dt);
	void draw(sf::RenderWindow &win);

	void setPos(sf::Vector2f pos);
	void setTexture(sf::Texture* texture);
	void setType(int type);
	void setScale(float scale);
	void setBounds(sf::IntRect bounds);
	void setColor(sf::Color color);
	void setVerbosity(bool print, bool draw);
	void setSpeed(float speed);
	void setRange(float range);
	void setName(std::string name);

	std::string getName();
};

