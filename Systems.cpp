#include "Systems.h"
//################## UPDATING	#################################################
void System_Update_Fish::Update(entt::registry& reg, sf::RenderWindow& win, float dt)
{

	auto view = reg.view<Component_Stats, Component_Behavior, Component_Graph>();

	//Get mouse pos
	sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(win).x ,(float)sf::Mouse::getPosition(win).y};

	view.each([dt, &win, mousePos](Component_Stats& s, Component_Behavior& b, Component_Graph& g) {
		//Increase hunger value
		b.hunger += b.hungerRate * dt;


		//Check For Grab
		if (g.sprite.getGlobalBounds().contains(mousePos)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (!b.goalChanged) {
					b.goal = 4;
					b.goalChanged = true;
				}
				
			}
		}

		switch (b.goal) {
		case 0:
			//## Idle
			//Handle State transition
			if (b.goalChanged) {
				if (s.isPrintVerbose) {
					std::cout << "Goal: Idle" << std::endl;
				}
				b.goalChanged = false;
			}

			//Do bobbing
			b.bobTimer += dt;
			if (b.bobTimer >= b.bobThreshold) {
				b.bobTimer = 0;
				g.sprite.move(0, b.bobDirection);

				b.bobDirection *= -1;

				//Do flip
				if (utl::randRange(0, 10) < 5) {
					g.sprite.scale(-1, 1);
				}
			}

			break;
		case 1:
			//## Moving
			//Handle State transition
			if (b.goalChanged) {
				if (s.isPrintVerbose) {
					std::cout << "Goal: Moving" << std::endl;
				}

				b.targetPos.x = utl::randRange(g.sprite.getPosition().x - b.range, g.sprite.getPosition().x + b.range);
				b.targetPos.y = utl::randRange(g.sprite.getPosition().y - b.range, g.sprite.getPosition().y + b.range);

				if (s.isPrintVerbose) {
					std::cout << "Init Target: (" << b.targetPos.x << ", " << b.targetPos.y << ")" << std::endl;
				}

				//Apply bounds
				if (b.targetPos.x >= b.bounds.width) {
					b.targetPos.x = b.bounds.width - 10;
				}

				if (b.targetPos.y >= b.bounds.height) {
					b.targetPos.y = b.bounds.height - 10;
				}

				if (b.targetPos.x < b.bounds.left) {
					b.targetPos.x = b.bounds.left + 10;
				}

				if (b.targetPos.y < b.bounds.top) {
					b.targetPos.y = b.bounds.top + 10;
				}


				b.angleToTarget = utl::getAngle(g.sprite.getPosition().x, g.sprite.getPosition().y, b.targetPos.x, b.targetPos.y);

				if (s.isPrintVerbose) {
					std::cout << "Target: (" << b.targetPos.x << ", " << b.targetPos.y << ")" << "@" << b.angleToTarget << std::endl;
				}

				b.goalChanged = false;
			}

			//Set sprite direction
			if (b.targetPos.x <= g.sprite.getPosition().x) {
				g.sprite.setScale(s.scale, s.scale);
			}
			else {
				g.sprite.setScale(-1 * s.scale, s.scale);
			}

			b.distToTarget = utl::dist(g.sprite.getPosition().x, g.sprite.getPosition().y, b.targetPos.x, b.targetPos.y);
			if (b.distToTarget <= .2) {
				//Then target reached, idle
				b.goal = 0;
				b.goalChanged = true;
				break;
			}
			else {
				//Just keep swimming
				float moveX = cosf(b.angleToTarget) * s.speed * dt;
				float moveY = sinf(b.angleToTarget) * s.speed * dt;
				g.sprite.move(moveX, moveY);
			}

			break;
		case 2:
			//## Fleeing
			if (b.goalChanged) {
				if (s.isPrintVerbose) {
					std::cout << "Goal: Fleeing" << std::endl;
				}


				b.goalChanged = 0;
			}
			else {
				//Get mouse pos
				b.fleeSource = { (float)sf::Mouse::getPosition(win).x,(float)sf::Mouse::getPosition(win).y };

				//Set sprite direction
				if (b.fleeSource.x <= g.sprite.getPosition().x) {
					g.sprite.setScale(-1 * s.scale, s.scale);
				}
				else {
					g.sprite.setScale(s.scale, s.scale);
				}


				b.angleToSource = utl::getAngle(g.sprite.getPosition().x, g.sprite.getPosition().y, b.fleeSource.x, b.fleeSource.y);


				float moveX = -1 * b.fleeSpeedMod * cosf(b.angleToSource) * s.speed * dt;
				float moveY = -1 * b.fleeSpeedMod * sinf(b.angleToSource) * s.speed * dt;


				g.sprite.move(moveX, moveY);

				//Apply bounds
				if (g.sprite.getPosition().x >= b.bounds.width - 10) {
					g.sprite.setPosition(b.bounds.width - 10, g.sprite.getPosition().y);
				}

				if (g.sprite.getPosition().y >= b.bounds.height - 10) {
					g.sprite.setPosition(g.sprite.getPosition().x, b.bounds.height - 10);
				}

				if (g.sprite.getPosition().x < b.bounds.left + 10) {
					g.sprite.setPosition(b.bounds.left + 10, g.sprite.getPosition().y);
				}

				if (g.sprite.getPosition().y < b.bounds.top + 10) {
					g.sprite.setPosition(g.sprite.getPosition().x, b.bounds.top + 10);
				}
			}



			break;
		case 3:
			//## Feeding

			break;
		case 4:
			//## Picked Up
			//State Change Logic
			if (b.goalChanged) {
				g.sprite.scale(1.25, 1.25);
				b.goalChanged = 0;
			}

			//State update logic
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				b.goal = 0;
				b.goalChanged = 1;
				g.sprite.scale(1 / 1.25, 1 / 1.25);
			}

			g.sprite.setPosition(mousePos);

			break;
		}



		//Check for flee
		sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(win).x , (float)sf::Mouse::getPosition(win).y };
		if (b.goal != 2 && utl::dist(g.sprite.getPosition().x, g.sprite.getPosition().y, mousePos.x, mousePos.y) <= b.fleeRange) {
			b.goal = 2;
			b.fleeSource = mousePos;
			b.goalChanged = true;
		}
		else if (b.goal == 2 && utl::dist(g.sprite.getPosition().x, g.sprite.getPosition().y, mousePos.x, mousePos.y) > b.fleeRange) {
			b.goal = 0;
			b.goalChanged = true;
		}

		//Make decision if idle
		if (b.goal == 0) {
			b.decisionTimer += dt;
		}


		if (b.decisionTimer >= b.decisionThreshold) {
			b.decisionTimer = 0;

			//Choose a new behavior
			b.goal = utl::randRange(0, 1);
			if (s.isPrintVerbose) {
				std::cout << "Decision made: " << b.goal << std::endl;
			}
			b.goalChanged = true;
		}
		});
}



//###################	RENDERING	##############################################
void System_Rendering::Render(entt::registry& reg, sf::RenderWindow& win)
{
	auto view = reg.view<Component_Graph>();

	view.each([&win](Component_Graph& g) {
		//Draw
		win.draw(g.sprite);
		});
}

