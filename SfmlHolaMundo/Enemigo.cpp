#include "stdafx.h"
#include "Enemigo.h"



using namespace sf;
Enemigo::Enemigo()
{
}

Enemigo::Enemigo(sf::Color color, int x, int y, sf::RectangleShape *&rectangle)
{
	rectangle->setSize(sf::Vector2f(100, 50));
	/*rectangle.setOutlineColor(sf::Color::Red);*/
	rectangle->setFillColor(color);
	rectangle->setOutlineThickness(2);
	rectangle->setPosition(x, y);
}


Enemigo::~Enemigo(){
}

bool isBeingHit(sf::Vector2f positionReader, sf::Vector2i mousePosition) {
	if (mousePosition.x >= (positionReader.x - 20) && mousePosition.x <= (positionReader.x + 100) && mousePosition.y >= (positionReader.y - 20) && mousePosition.y <= (positionReader.y + 50))
		return true;
	return false;
}


bool Enemigo::checkShot(sf::RenderWindow &window, sf::CircleShape &shape, sf::RectangleShape *&rectangle) {

	auto positionReader = rectangle->getPosition();
	auto mousePosition = Mouse::getPosition(window);
	auto newX = rand() % ScreenWidth + 1;
	auto newY = rand() % ScreenHeight + 1;

	/*system("cls");
	std::cout << "Mouse X: " << mousePosition.x << std::endl;
	std::cout << "Mouse Y: " << mousePosition.y << std::endl;
	std::cout << "Rect X: " << positionReader.x << std::endl;
	std::cout << "Rect Y: " << positionReader.y << std::endl;
	std::cout << "New X: " << newX << "New Y: " << newY << "Health: "<<health <<std::endl;*/


	if (mousePosition.x >= (positionReader.x - 20) && mousePosition.x <= (positionReader.x + 100) && mousePosition.y >= (positionReader.y - 50) && mousePosition.y <= (positionReader.y + 50) && alreadyHit == false) {
		shape.setFillColor(Color::Red);
		health -= 10;
		if (health == 0) {
			rectangle->setPosition(newX, newY);
			health = 40;
			respawns++;
		}
		if (respawns == 4) {
			std::cout << "DEAD" << std::endl;
			isDead = true;
			return isDead;
		}

		alreadyHit = true;
		//std::cout << "Hit" << std::endl;
	}

	return isDead;
}

void Enemigo::checkMouseHover(sf::RectangleShape *&rectangle, sf::RenderWindow &window, sf::CircleShape &shape) {
	auto positionReader = rectangle->getPosition();
	auto mousePosition = sf::Mouse::getPosition(window);

	if (isBeingHit(positionReader, mousePosition)) {
		shape.setFillColor(sf::Color::Blue);
	}
	else {
		shape.setFillColor(sf::Color::Green);
	}

}

void Enemigo::move(sf::RectangleShape *&rectangle) {
	auto oldPosition = rectangle->getPosition();
	double newX = oldPosition.x, newY = oldPosition.y;


	//Caso 1 el enemigo se movera para la izquierda
	//Caso 2 el enemigo se movera para arriba
	//Caso 3 el enemigo se movera por los dos sentidos

	switch (rand() % 3 + 1) {
	case 1:
		if (oldPosition.x < ScreenWidth - 100) {
			newX = oldPosition.x + rand() % 1 + 0.1;
			newY = oldPosition.y;
		}
		break;
	case 2:
		if (oldPosition.y < ScreenHeight - 50) {
			newX = oldPosition.x;
			newY = oldPosition.y - 0.1 - rand() % 1 + 0.1;
		}
		else if (oldPosition.y >= ScreenHeight - 50) {
			newX = oldPosition.x;
			newY = oldPosition.y + 0.1 + rand() % 1 + 0.1;
		}
		break;
	case 3:
		if (oldPosition.x < ScreenWidth - 100 && oldPosition.y < ScreenHeight - 50 && isGoingUp == false) {
			newX = oldPosition.x + +rand() % 2 + 0.1;
			newY = oldPosition.y + rand() % 2 + 0.1;
		}
		else {
			isGoingUp = true;
			newX = oldPosition.x - rand() % 2 + 0.1;
			newY = oldPosition.y - rand() % 3 + 0.1;
			if (oldPosition.y < 0)
				isGoingUp = false;
			else if (oldPosition.x > 800) {
				isGoingUp = true;
			}

		}
		//
		break;
	}

	/*std::cout <<"X: " << oldPosition.x << std::endl;
	std::cout << "Y: " << oldPosition.y << std::endl;*/

	rectangle->setPosition(newX, newY);
}

void Enemigo::restart()
{
	health = 20;
	respawns = 0;
	isDead = false;
}
