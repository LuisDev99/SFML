// SfmlHolaMundo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include  <SFML/Window.hpp>
#include <Windows.h>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "Enemigo.h"

#define ScreenWidth 1000
#define ScreenHeight 400
using namespace sf;

RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
RectangleShape *rectangle = new RectangleShape();
RectangleShape *rectangle1 = new RectangleShape();

CircleShape shape(10.f);
Font font;

Texture texture;

bool isDead = false, isDead1 = false;

void setupRectangle();
void setupCircle();
void setupFont();
//void checkShot();

int main()
{

	texture.loadFromFile("images.jpg");
	Sprite backg(texture);
	
	setupRectangle();
	setupCircle();
	setupFont();

	Vector2i position = Mouse::getPosition(window); //sf::Mouse::setPosition(sf::Vector2i(100, 200), window); 
	window.setMouseCursorVisible(false);

	Enemigo enemy(sf::Color::White, 0, 0, rectangle);
	Enemigo enemy1(sf::Color::Red, 60, 0, rectangle1);

	while (window.isOpen())
	{
		
		enemy.move(rectangle);
		enemy1.move(rectangle1);

		position = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			isDead = enemy.checkShot(window, shape, rectangle);
			isDead1 = enemy1.checkShot(window, shape, rectangle1);
			
		} else {
			shape.setFillColor(Color::Green);
			enemy.alreadyHit = false;
			enemy1.alreadyHit = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::H)) {
			rectangle->setPosition(10, 20);
			rectangle1->setPosition(50, 50);
	
			if (enemy.isDead == true)
				enemy.restart();
			if (enemy1.isDead == true)
				enemy1.restart();
			
		}
			

		window.clear();

		//Todo codigo de aqui de dibujar 

		if (isDead == false)
			window.draw(*rectangle);

		if (isDead1 == false)
			window.draw(*rectangle1);
		//window.draw(backg);
		window.draw(shape);
		shape.setPosition(position.x, position.y);
		//Fin

		window.display();
	}

	return 0;
}


void setupRectangle() {
	rectangle->setSize(sf::Vector2f(100, 50));
	/*rectangle.setOutlineColor(sf::Color::Red);*/
	rectangle->setOutlineThickness(2);
	rectangle->setPosition(10, 20);

}

void setupCircle() {

	shape.setFillColor(sf::Color::Green);
}

void setupFont() {
	if (!font.loadFromFile("YARDSALE.ttf"))
		throw("ERROR LOADING");

	Text text;
	text.setFont(font); // font is a sf::Font
	text.setString("Hello world");
	text.setCharacterSize(24); // in pixels, not poin
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

}

//void checkShot() {
//
//	auto positionReader = rectangle->getPosition();
//	auto mousePosition = Mouse::getPosition(window);
//	auto newX = rand() % ScreenWidth + 1;
//	auto newY = rand() % ScreenHeight + 1;
//
//	/*system("cls");
//	std::cout << "Mouse X: " << mousePosition.x << std::endl;
//	std::cout << "Mouse Y: " << mousePosition.y << std::endl;
//	std::cout << "Rect X: " << positionReader.x << std::endl;
//	std::cout << "Rect Y: " << positionReader.y << std::endl;
//	std::cout << "New X: " << newX << "New Y: " << newY << "Health: "<<health <<std::endl;*/
//
//
//	if (mousePosition.x >= (positionReader.x - 20) && mousePosition.x <= (positionReader.x + 100) && mousePosition.y >= (positionReader.y - 50) && mousePosition.y <= (positionReader.y + 50) && alreadyHit == false) {
//		shape.setFillColor(Color::Red);
//		health -= 10;
//		if (health == 0) {
//			rectangle->setPosition(newX, newY);
//			health = 40;
//		}
//		alreadyHit = true;
//		std::cout << "Hit" << std::endl;
//	}
//}

/*if(shape.getFillColor() == Color::Green)
shape.setFillColor(Color::Red);*/