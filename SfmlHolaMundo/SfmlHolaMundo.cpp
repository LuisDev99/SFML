// SfmlHolaMundo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Font font;
	if (!font.loadFromFile("YARDSALE.ttf"))
		throw("ERROR LOADING");

	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font

						// set the string to display
	text.setString("Hello world");

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

							   // set the color
	//text.setColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	


	




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(shape);
		// inside the main loop, between window.clear() and window.display()
		window.draw(text);
		window.display();
	}

	return 0;
}

