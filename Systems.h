#pragma once
#include <iostream>
#include "entt.hpp"
#include "Component.hpp"
#include "Util.h"

/*
Project: Entt Game Engine
Author: Sam Daly
Created: 17 JAN 2024
Updated: 3 FEB 2024
*/

/* Description:
The purpose of this code is to declare and define the systems that operate upon the entites in a given scene. There are two main
categories that systems are divided into; Systems that update component states, denoted as System_Update_X, and Systems that
render components, denoted as System_Render_X. Updating systems are called by a function of the form Update(entt::registry &reg, float dt).
Rendering systems are called by a function of the form Render(entt::registry &reg, sf::RenderWindow &win);
*/


//###################### UPDATING ###########################################

struct System_Update_Fish {
	void Update(entt::registry& reg, sf::RenderWindow &win, float dt);
};


//########################### RENDERING #################################

struct System_Rendering {
	void Render(entt::registry& reg, sf::RenderWindow& win);
};