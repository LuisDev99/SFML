
#include "Enemigo.h"
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

static bool hit = false;


using namespace sf;
using namespace std;


Enemigo::Enemigo(std::_Binder < std::_Unforced, std::uniform_int_distribution<int> &, std::reference_wrapper<std::default_random_engine>>random, sf::Color color)
{
	distribution = std::uniform_int_distribution<int>(-16, 16);
	direction = sf::Vector2f(random(), random());
	velocity = 20;
	update_ms = sf::seconds(1.f / 30.f);

	ball = sf::CircleShape(ball_radius - 4);
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(color);
	ball.setOrigin(ball_radius / 2, ball_radius / 2);
	ball.setPosition(window_width / 2, window_height / 2);

}

Enemigo::Enemigo() {

}


Enemigo::~Enemigo(){
}

bool isBeingHit(sf::Vector2f positionReader, sf::Vector2i mousePosition) {
	if (mousePosition.x >= (positionReader.x - 20) && mousePosition.x <= (positionReader.x + 100) && mousePosition.y >= (positionReader.y - 20) && mousePosition.y <= (positionReader.y + 50))
		return true;
	return false;
}

bool Enemigo::checkShotCircle(sf::RenderWindow &window, sf::CircleShape &shape) {
	auto posicion = shape.getPosition();
	auto mousePosicion = Mouse::getPosition();
	auto newX = rand() % ScreenWidth + 1;
	auto newY = rand() % ScreenHeight + 1;

	if (mousePosicion.x >= (posicion.x - 260) && mousePosicion.x <= (posicion.x + 260) && mousePosicion.y >= (posicion.y - 260) && mousePosicion.y <= (posicion.y + 260) && hit == false) {
		shape.setFillColor(Color::Red);
		return true;
	}
	return false;
}


void Enemigo::restart()
{
	health = 20;
	respawns = 0;
	isDead = false;
}

void Enemigo::moveCircle()
{
	const auto pos = ball.getPosition();
	const auto delta = update_ms.asSeconds() * velocity;
	sf::Vector2f new_pos(pos.x + direction.x * delta, pos.y + direction.y * delta);

	if (new_pos.x - ball_radius < 0) {
		direction.x *= -1;
		new_pos.x = 0 + ball_radius;
	} else if (new_pos.x + ball_radius >= window_width) {
		direction.x *= -1;
		new_pos.x = window_width - ball_radius;
	} else if (new_pos.y - ball_radius < 0) {
		direction.y *= -1;
		new_pos.y = 0 + ball_radius;
	} else if (new_pos.y + ball_radius >= window_height) {
		direction.y *= -1;
		new_pos.y = window_height - ball_radius;
	}
	ball.setPosition(new_pos);
}
