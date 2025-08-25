#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entt.hpp"
#include "Systems.h"

//######### BASE SCENE CLASS ############################

class Scene {
protected:
	//Common Data
	Scene* next = nullptr;
	entt::registry* reg;
	sf::RenderWindow* win;
	std::vector<sf::Texture*>* textures;


public:
	//Common Functions
	void setNext(Scene* targ);
	void setRegistry(entt::registry* reg);
	void setWindow(sf::RenderWindow* win);
	void setTextures(std::vector<sf::Texture*>* textures);

	//Virtual Functions
	virtual void poll(sf::Event event) = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void end() = 0;
};


//######### MAIN SCENE CLASS ############################
class Scene_Main : public Scene {
private:
	//### Data
	System_Update_Fish system_update_fish;
	System_Rendering system_renderer;

	//### Init
	void initTest();

public:
	//### Constructor and Destructor
	Scene_Main();
	Scene_Main(entt::registry* registry, sf::RenderWindow* window, std::vector<sf::Texture*>* textures);
	~Scene_Main();


	//### Primary Functions
	void poll(sf::Event event);
	void update(float dt);
	void render();
	void end();
};
