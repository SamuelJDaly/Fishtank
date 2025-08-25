#include "Engine.h"


//################	DRIVER CODE	#################
int main() {
	//Vars
	Engine* engine = new Engine();

	//Engine loop
	while (engine->getRunning()) {
		engine->poll();
		engine->update();
		engine->draw();
	}

	//Deallocate
	delete engine;
	return 0;
}