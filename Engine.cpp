#include "Engine.h"

//################## INIT #############################################
void Engine::initWindow()
{
	unsigned int width = sf::VideoMode::getDesktopMode().width;
	unsigned int height = sf::VideoMode::getDesktopMode().height;
	win.create(sf::VideoMode(width - 20, height - 20), "Fishtank", sf::Style::None);

	HWND hwnd = win.getSystemHandle(); // Get the native window handle
	// Set window to be layered
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
	// Set the alpha value for transparency (0 = fully transparent, 255 = fully opaque)
	SetLayeredWindowAttributes(hwnd, RGB(255, 255, 255), 255, LWA_COLORKEY | LWA_ALPHA);
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
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



}

void Engine::initScene()
{
	currScene = new Scene_Main(&reg, &win, &textures);
}






//####################### CONSTRUCTOR AND DESTRUCTOR ####################
Engine::Engine()
{
	srand(std::time(NULL));

	initWindow();
	initTextures();
	initScene();
}

Engine::~Engine()
{
	if (currScene) {
		delete currScene;
	}

	for (auto i : textures) {
		delete i;
	}
}







//###################### PRIMARY FUNCTIONS ###############################
//##### Poll
void Engine::poll()
{
	while (win.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			win.close();
			isRunning = false;
		}

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
			win.close();
			isRunning = false;
		}

		currScene->poll(event);
	}
}

//##### Update
void Engine::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		win.close();
		isRunning = false;
	}

	dt = engineClk.getElapsedTime().asSeconds();
	engineClk.restart();

	currScene->update(dt);
}

//##### Draw
void Engine::draw()
{
	win.clear(sf::Color::White);

	currScene->render();

	win.display();
}

bool Engine::getRunning()
{
	return isRunning;
}
