#include "Engine.h"

//############## INIT ################################################
void Engine::initWindow()
{
	window.create(sf::VideoMode(1200,800), "Fishtank");
}

void Engine::initTextures()
{
	textures.push_back(new sf::Texture());
	textures.back()->loadFromFile("resource/textures/darter.png");

	textures.push_back(new sf::Texture());
	textures.back()->loadFromFile("resource/textures/fiddler.png");

	textures.push_back(new sf::Texture());
	textures.back()->loadFromFile("resource/textures/sawfish.png");

	textures.push_back(new sf::Texture());
	textures.back()->loadFromFile("resource/textures/club.png");

	textures.push_back(new sf::Texture());
	textures.back()->loadFromFile("resource/textures/spadefish.png");

	textures.push_back(new sf::Texture());
	textures.back()->loadFromFile("resource/textures/boomerang.png");

	textures.push_back(new sf::Texture());
	textures.back()->loadFromFile("resource/textures/gar.png");
}

void Engine::initFictionary()
{
	//Orange darter
	Fish orangeDarter;
	orangeDarter.setTexture(textures.at(0));
	orangeDarter.setBounds(tankBounds);
	orangeDarter.setColor(sf::Color(253,126,22));
	orangeDarter.setScale(1.5);
	orangeDarter.setSpeed(30);
	orangeDarter.setRange(100);
	orangeDarter.setName("Orange Darter");
	fictionary.push_back(orangeDarter);

	//Red Fiddler
	Fish redFiddler;
	redFiddler.setTexture(textures.at(1));
	redFiddler.setBounds(tankBounds);
	redFiddler.setColor(sf::Color(255, 0, 0));
	redFiddler.setScale(2);
	redFiddler.setSpeed(25);
	redFiddler.setRange(100);
	redFiddler.setName("Red Fidder");
	fictionary.push_back(redFiddler);

	//Green Sawfish
	Fish greenSawfish;
	greenSawfish.setTexture(textures.at(2));
	greenSawfish.setBounds(tankBounds);
	greenSawfish.setColor(sf::Color(41, 234, 160));
	greenSawfish.setScale(2.3);
	greenSawfish.setSpeed(10);
	greenSawfish.setRange(100);
	greenSawfish.setName("Green Sawfish");
	fictionary.push_back(greenSawfish);

	//Pink Club
	Fish pinkClub;
	pinkClub.setTexture(textures.at(3));
	pinkClub.setBounds(tankBounds);
	pinkClub.setColor(sf::Color(242, 21, 255));
	pinkClub.setScale(2);
	pinkClub.setSpeed(20);
	pinkClub.setRange(100);
	pinkClub.setName("Pink Club");
	fictionary.push_back(pinkClub);

	//Blue Spadefish
	Fish blueSpadefish;
	blueSpadefish.setTexture(textures.at(4));
	blueSpadefish.setBounds(tankBounds);
	blueSpadefish.setColor(sf::Color(0, 0, 255));
	blueSpadefish.setScale(2.5);
	blueSpadefish.setSpeed(20);
	blueSpadefish.setRange(100);
	blueSpadefish.setName("Blue Spadefish");
	fictionary.push_back(blueSpadefish);

	//Yellow Boomerang
	Fish yellowBoomerang;
	yellowBoomerang.setTexture(textures.at(5));
	yellowBoomerang.setBounds(tankBounds);
	yellowBoomerang.setColor(sf::Color(255, 255, 0));
	yellowBoomerang.setScale(1);
	yellowBoomerang.setSpeed(20);
	yellowBoomerang.setRange(100);
	yellowBoomerang.setName("Yellow Boomerang");
	fictionary.push_back(yellowBoomerang);

	//Yellowbelly Gar
	Fish yellowbellyGar;
	yellowbellyGar.setTexture(textures.at(6));
	yellowbellyGar.setBounds(tankBounds);
	yellowbellyGar.setScale(2);
	yellowbellyGar.setSpeed(20);
	yellowbellyGar.setRange(200);
	yellowbellyGar.setName("Yellowbelly Gar");
	//fictionary.push_back(yellowbellyGar);
}

void Engine::initTest()
{
	
}


//############## CONSTRUCTORS AND DESTRUCTORS #######################
Engine::Engine()
{
	//Random Seed
	srand(std::time(NULL));

	initWindow();
	initTextures();
	initFictionary();
	initTest();
}

Engine::~Engine()
{
	//De allocate fish
	for (auto i : fish) {
		delete i;
	}

	//De allocate textures
	for (auto i : textures) {
		delete i;
	}
}


//############### PRIMARY FUNCTIONS	###############################
void Engine::poll()
{
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			this->isRunning = false;
		}

		if (event.type == sf::Event::MouseButtonReleased) {
			sf::Vector2f mousePos = {(float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y};

			//Place a random fish
			int type = utl::randRange(0, (int)fictionary.size() - 1);
			std::cout << "Placing a  " << fictionary.at(type).getName() << std::endl;
			Fish* fishToPlace = new Fish(fictionary.at(type));
			fishToPlace->setPos(mousePos);
			fish.push_back(fishToPlace);
		}
	}
}

void Engine::update()
{
	dt = engineClk.getElapsedTime().asSeconds();
	engineClk.restart();

	poll();

	for (auto i : fish) {
		i->update(dt);
	}
	
}

void Engine::draw()
{
	window.clear();

	for (auto i : fish) {
		i->draw(window);
	}

	window.display();
}

bool Engine::getRunning()
{
	return isRunning;
}
