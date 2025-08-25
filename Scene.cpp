#include "Scene.h"

//###########################	BASE CLASS	#################################

void Scene::setNext(Scene* targ)
{
	next = targ;
}

void Scene::setRegistry(entt::registry* reg)
{
	this->reg = reg;
}

void Scene::setWindow(sf::RenderWindow* win)
{
	this->win = win;
}

void Scene::setTextures(std::vector<sf::Texture*>* textures)
{
	this->textures = textures;
}



//###########################	MAIN SCENE	#################################

//################ INIT
void Scene_Main::initTest()
{
	
}

//################	CONSTRUCTOR AND DESTRUCTOR
Scene_Main::Scene_Main()
{
	this->initTest();
}

Scene_Main::Scene_Main(entt::registry* registry, sf::RenderWindow* window, std::vector<sf::Texture*>* textures)
{
	this->reg = registry;
	this->win = window;
	this->textures = textures;
	this->initTest();
}

Scene_Main::~Scene_Main()
{
}

//################ PRIMARY FUNCTIONS

void Scene_Main::poll(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased) {
		sf::Vector2i clickPos = sf::Mouse::getPosition(*win);

		if (event.key.code == sf::Mouse::Right) {
			std::cout << "{" << clickPos.x << ", " << clickPos.y << "}" << std::endl;

			auto e = reg->create();

			auto& g = reg->emplace<Component_Graph>(e);
			g.sprite.setTexture(*textures->at(1));
			g.sprite.setPosition({ (float)clickPos.x,(float)clickPos.y });
			g.sprite.setColor(sf::Color(utl::randRange(0,255), utl::randRange(0, 255), utl::randRange(0, 255)));

			auto& s = reg->emplace<Component_Stats>(e);

			auto& b = reg->emplace<Component_Behavior>(e);
		}
	}
}

void Scene_Main::update(float dt)
{
	system_update_fish.Update(*reg, dt);
}

void Scene_Main::render()
{
	system_renderer.Render(*reg, *win);
}

void Scene_Main::end() {

}



