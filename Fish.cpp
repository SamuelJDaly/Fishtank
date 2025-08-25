#include "Fish.h"

Fish::Fish()
{
	targLine[0] = sf::Vertex(sprite.getPosition());
	targLine[1] = sf::Vertex(targetPos);
	targLine[0].color = sf::Color::Green;
	targLine[1].color = sf::Color::Green;
}

Fish::~Fish()
{
}

void Fish::update(float dt)
{
	hunger += hungerRate * dt;

	switch (goal) {
	case 0:
		//Idle, bob up and down
		if (goalChange) {
			if (printVerbose) {
				std::cout << "State: Idle" << std::endl;
			}
			goalChange = 0;
		}

		bobTimer += dt;
		if (bobTimer >= bobThreshold) {
			bobTimer = 0;
			sprite.move(0, bobDirection);
			bobDirection *= -1;
		}


		break;
	case 1:
		//Move to target
		//Set a target if goal has changed
		if (goalChange) {
			if (printVerbose) {
				std::cout << "State: Moving" << std::endl;
			}

			targetPos.x = utl::randRange(sprite.getPosition().x - targetRange, sprite.getPosition().x + targetRange);
			targetPos.y = utl::randRange(sprite.getPosition().y - targetRange, sprite.getPosition().y + targetRange);

			//Apply bounds
			if (targetPos.x >= bounds.width) {
				targetPos.x = bounds.width - 10;
			}

			if (targetPos.y >= bounds.height) {
				targetPos.y = bounds.height - 10;
			}

			if (targetPos.x < bounds.left) {
				targetPos.x = bounds.left + 10;
			}

			if (targetPos.y < bounds.top) {
				targetPos.y = bounds.top + 10;
			}


			targetAngle = utl::getAngle(sprite.getPosition().x, sprite.getPosition().y, targetPos.x, targetPos.y);
			if (printVerbose) {
				std::cout << "Target: (" << targetPos.x << ", " << targetPos.y << ")" << "@" << targetAngle << std::endl;
			}
			targLine[0].position = sprite.getPosition();
			targLine[1].position = targetPos;
			goalChange = 0;
		}

		//Set sprite direction
		if (targetPos.x <= sprite.getPosition().x) {
			sprite.setScale(scale, scale);
		}
		else {
			sprite.setScale(-1 * scale, scale);
		}

		targetDist = utl::dist(sprite.getPosition().x, sprite.getPosition().y, targetPos.x, targetPos.y);
		if (targetDist <= .5) {
			//Then target reached, idle
			goal = 0;
			goalChange - 1;
			break;
		}
		else {
			//Just keep swimming
			float moveX = cosf(targetAngle) * speed * dt;
			float moveY = sinf(targetAngle) * speed * dt;
			sprite.move(moveX, moveY);
			targLine[0].position = sprite.getPosition();
		}

		break;
	case 2:
		//Flee, get as far away from source as possible
		if (goalChange) {
			if (printVerbose) {
				std::cout << "State: Flee" << std::endl;
			}
			goalChange = 0;
		}
		break;
	case 3:
		//Eat, find a nearby smaller fish and eat it

		break;
	}


	if (goal == 0) {
		decisionTimer += dt;
	}

	if (decisionTimer >= decisionThreshold) {
		decisionTimer = 0;

		//Choose a new behavior
		goal = utl::randRange(0, 1);
		if (printVerbose) {
			std::cout << "Decision made: " << goal << std::endl;
		}
		goalChange = 1;
	}
}

void Fish::draw(sf::RenderWindow& win)
{
	win.draw(sprite);

	if (drawVerbose && goal != 0) {
		win.draw(&targLine[0], 2, sf::LinesStrip);
	}
}

void Fish::setPos(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Fish::setTexture(sf::Texture* texture)
{
	this->texture = texture;
	sprite.setTexture(*this->texture);
	sprite.setOrigin(this->texture->getSize().x / 2, this->texture->getSize().y / 2);
}

void Fish::setType(int type)
{
	this->type = type;
}

void Fish::setScale(float scale)
{
	this->scale = scale;
	sprite.setScale(scale, scale);
}

void Fish::setBounds(sf::IntRect bounds)
{
	this->bounds = bounds;
}

void Fish::setColor(sf::Color color)
{
	this->color = color;
	sprite.setColor(color);
}

void Fish::setVerbosity(bool print, bool draw)
{
	printVerbose = print;
	drawVerbose = draw;
}

void Fish::setSpeed(float speed)
{
	this->speed = speed;
}

void Fish::setRange(float range)
{
	this->targetRange = range;
}

void Fish::setName(std::string name)
{
	this->name = name;
}

std::string Fish::getName()
{
	return name;
}
