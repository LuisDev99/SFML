#pragma once

#include <SFML/Graphics.hpp>
#include  <SFML/Window.hpp>
#include <Windows.h>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "Enemigo.h"
#include <random>
#include <functional>
#include <cstdlib>
#include <cmath>
#include "Menu.h"

#define ScreenWidth 1000
#define ScreenHeight 400
class Enemigo
{
public:
	Enemigo();
	Enemigo(std::_Binder < std::_Unforced, std::uniform_int_distribution<int> &, std::reference_wrapper<std::default_random_engine>>random, sf::Color);
	

	//Game
	std::random_device seed_device;
	std::default_random_engine engine;
	std::uniform_int_distribution<int> distribution;
	sf::CircleShape ball;
	sf::Vector2f direction;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Time update_ms;

	float velocity;
	const int window_width = 1000;
	const int window_height = 400;
	const float ball_radius = 30.f;
	const int bpp = 32;

	int health = 40;
	int respawns = 0;
	bool isGoingUp = false;
	bool alreadyHit = false;
	bool isDead = false;
	//void crearPelota();
	static bool checkShotCircle(sf::RenderWindow &, sf::CircleShape &);
	void restart();
	void moveCircle();

	~Enemigo();
};

