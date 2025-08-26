#pragma once
#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "entt.hpp"
#include "Scene.h"



class Engine {
private:
	//#### Data
	bool isRunning = true;
	sf::RenderWindow win;
	entt::registry reg;

	sf::Event event;
	sf::Clock engineClk;
	float dt = 0;

	std::vector<sf::Texture*> textures;

	Scene* currScene;

	//#### Init
	void initWindow();
	void initTextures();
	void initScene();

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