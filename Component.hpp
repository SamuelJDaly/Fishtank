#pragma once
#include<SFML/Graphics.hpp>


struct Component_Graph {
	sf::Sprite sprite;
};

struct Component_Stats {
	float speed = 10; //px/s
	float scale = 1;
	int size = 0;

	bool isPrintVerbose = false;
	bool isDrawVerbose = false;
};

struct Component_Behavior {
	int goal = 0;
	bool goalChanged = false;

	sf::IntRect bounds = { 0,0,1,1 };

	float decisionTimer = 0;
	float decisionThreshold = 3;
	
	float bobTimer = 0;
	float bobThreshold = 1;
	int bobDirection = -1;

	sf::Vector2f targetPos = {0,0};
	float angleToTarget = 0;
	float distToTarget = 0;
	float range = 50;

	sf::Vector2f fleeSource = { 0,0 };
	float angleToSource = 0;
	float fleeRange = 50;

	float hunger = 0;
	float hungerRate = 1; //Hunger increase per second
};