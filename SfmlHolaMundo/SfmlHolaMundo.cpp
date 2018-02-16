// SfmlHolaMundo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include  <SFML/Window.hpp>
#include <Windows.h>
#include <SFML/Window/Mouse.hpp>

#define ScreenWidth 1000
#define ScreenHeight 500
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);

	Vector2i position = Mouse::getPosition(window); //Get Cursor position
	//sf::Mouse::setPosition(sf::Vector2i(100, 200), window); //Set Mouse position

	sf::Font font;
	if (!font.loadFromFile("YARDSALE.ttf"))
		throw("ERROR LOADING");

	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font

    // set the string to display
	text.setString("Hello world");

	// set the character size
	text.setCharacterSize(24); // in pixels, not poin
	
	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	//Ocultar el mouse
	window.setMouseCursorVisible(false);

	//Mouse
	

	while (window.isOpen())
	{
		position = Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
		
			if(shape.getFillColor() == sf::Color::Green)
				shape.setFillColor(sf::Color::Red);
			else if (shape.getFillColor() == sf::Color::Red)
				shape.setFillColor(sf::Color::Blue);
			else if (shape.getFillColor() == sf::Color::Blue)
				shape.setFillColor(sf::Color::Green);
		}

		window.clear();
		window.draw(shape);
		shape.setPosition(position.x, position.y);

		//inside the main loop, between window.clear() and window.display()
		//window.draw(text);
		window.display();
	}

	return 0;
}

