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
	for (int i = 0; i < 3; i++) {
		float scale = utl::randRange(2.0f, 3.0f);

		auto e = reg->create();

		auto& g = reg->emplace<Component_Graph>(e);
		g.sprite.setTexture(*textures->at(1));
		g.sprite.setOrigin(g.sprite.getTexture()->getSize().x / 2, g.sprite.getTexture()->getSize().y / 2);
		g.sprite.setPosition({ utl::randRange(0.f, 1200.f),utl::randRange(0.f, 800.f) });
		g.sprite.setColor(sf::Color(utl::randRange(0, 255), utl::randRange(0, 255), utl::randRange(0, 255)));
		g.sprite.setScale({ scale,scale });

		auto& s = reg->emplace<Component_Stats>(e);
		s.scale = scale;
		s.isPrintVerbose = true;

		auto& b = reg->emplace<Component_Behavior>(e);
		b.range = (float)win->getSize().x;
		b.bounds = { 0,0, (int)win->getSize().x ,(int)win->getSize().y };
	}
}

void Scene_Main::addFishRnd()
{
	float scale = utl::randRange(2.0f, 3.0f);

	auto e = reg->create();

	auto& g = reg->emplace<Component_Graph>(e);
	g.sprite.setTexture(*textures->at(1));
	g.sprite.setOrigin(g.sprite.getTexture()->getSize().x / 2, g.sprite.getTexture()->getSize().y / 2);
	g.sprite.setPosition({ utl::randRange(0.f, 1200.f),utl::randRange(0.f, 800.f) });
	g.sprite.setColor(sf::Color(utl::randRange(0, 255), utl::randRange(0, 255), utl::randRange(0, 255)));
	g.sprite.setScale({ scale,scale });

	auto& s = reg->emplace<Component_Stats>(e);
	s.scale = scale;

	auto& b = reg->emplace<Component_Behavior>(e);
	b.bounds = { 0,0, (int)win->getSize().x ,(int)win->getSize().y };
	b.range = (float)win->getSize().x;
}

void Scene_Main::addFishRnd(sf::Vector2f pos)
{
	float scale = utl::randRange(2.0f, 3.0f);

	auto e = reg->create();

	auto& g = reg->emplace<Component_Graph>(e);
	g.sprite.setTexture(*textures->at(1));
	g.sprite.setOrigin(g.sprite.getTexture()->getSize().x / 2, g.sprite.getTexture()->getSize().y / 2);
	g.sprite.setPosition({ (float)pos.x,(float)pos.y });
	g.sprite.setColor(sf::Color(utl::randRange(0, 255), utl::randRange(0, 255), utl::randRange(0, 255)));
	g.sprite.setScale({ scale,scale });

	auto& s = reg->emplace<Component_Stats>(e);
	s.scale = scale;

	auto& b = reg->emplace<Component_Behavior>(e);
	b.bounds = { 0,0, (int)win->getSize().x ,(int)win->getSize().y };
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
	if (event.type == sf::Event::KeyReleased) {
		if (utl::randRange(0,1)) {
			addFishRnd();
		}
	}

	if (event.type == sf::Event::MouseButtonReleased) {
		sf::Vector2i clickPos = sf::Mouse::getPosition(*win);

		if (event.key.code == sf::Mouse::Right) {
			addFishRnd({(float)clickPos.x, (float)clickPos.y});
		}
	}
}

void Scene_Main::update(float dt)
{
	system_update_fish.Update(*reg, *win, dt);

	

	if (dbTimer >= dbThreshold) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			keyFlag = 1;
		}
	}
	else {
		dbTimer += dt;
	}

	if (keyFlag) {
		switch (keyFlag) {
		case 1:
			addFishRnd();
			break;
		}
		dbTimer = 0;
		keyFlag = 0;
	}


}

void Scene_Main::render()
{
	system_renderer.Render(*reg, *win);
}

void Scene_Main::end() {

}



