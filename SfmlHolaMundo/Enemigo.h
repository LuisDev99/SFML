#pragma once

#include <SFML/Graphics.hpp>
#include  <SFML/Window.hpp>
#include <Windows.h>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#define ScreenWidth 1000
#define ScreenHeight 400
class Enemigo
{
public:
	Enemigo();
	Enemigo(sf::Color, int, int, sf::RectangleShape *&);

	int health = 40;
	int respawns = 0;
	bool isGoingUp = false;
	bool alreadyHit = false;
	bool isDead = false;
	bool checkShot(sf::RenderWindow &, sf::CircleShape&, sf::RectangleShape *&);
	void checkMouseHover(sf::RectangleShape *&, sf::RenderWindow &, sf::CircleShape &);
	void move(sf::RectangleShape *&);
	void restart();

	~Enemigo();
};

