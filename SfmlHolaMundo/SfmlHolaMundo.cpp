// SfmlHolaMundo.cpp : Defines the entry point for the console application.
//


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
#include <vector>

#define ScreenWidth 1000
#define ScreenHeight 400
using namespace sf;
using namespace std;

RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
RenderWindow window2(VideoMode(ScreenWidth, ScreenHeight), "SFML works!");

CircleShape shapeDA(10.f);
CircleShape shapeIA(10.f);
CircleShape shapeDB(10.f);
CircleShape shapeIB(10.f);
Font font;


Texture texture;

bool isDead = false, isDead1 = false;


bool yaDisparo = false;
vector<Enemigo *> enemigos;

int balas = 8;
int puntaje = 0;
void setupCircle();
void setupFont();
void crearPelota();
void puntuacion();
bool verificar_dead();
void respawnRandomEnemies(std::_Binder < std::_Unforced, std::uniform_int_distribution<int> &, std::reference_wrapper<std::default_random_engine>> random);
//void checkShot();

void puntosPartidas() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML WORK!");
	while (window.isOpen())
	{

	}
	window.clear();
	window.display();
}

int menuOption() {


	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML WORK!");

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 1:
						std::cout << "jugar apretado" << std::endl;
						return 1;
						break;
					case 2:
						std::cout << "puntuacion apretado" << std::endl;
						return 2;
						break;
					case 3:
						window.close();
						return 3;
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();

		menu.draw(window);
		
		window.display();
	}

	return 0;
}


void game() {
	RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
	font.loadFromFile("YARDSALE.ttf");
	enemigos.clear();
	puntaje = 0;

	Text text;
	text.setFont(font); // font is a sf::Font
	string num = std::to_string(balas);
	text.setString(num);
	text.setCharacterSize(24); // in pixels, not poin
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);


	Text text1;
	text1.setFont(font); // font is a sf::Font
	string num1 = std::to_string(puntaje);
	text1.setString(num1);
	text1.setCharacterSize(24); // in pixels, not poin
	text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text1.setPosition(140, 0);

	setupCircle();
	Vector2i position = Mouse::getPosition(window); //sf::Mouse::setPosition(sf::Vector2i(100, 200), window); 
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);

	std::random_device seed_device;
	std::default_random_engine engine(seed_device());
	std::uniform_int_distribution<int> distribution(-16, 16);

	//Valores random para el movement
	auto random = std::bind(distribution, std::ref(engine));

	//Direccion random
	sf::Vector2f direction(random(), random());
	const float velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);


	sf::Clock clock;
	sf::Time elapsed = clock.restart();
	const sf::Time update_ms = sf::seconds(1.f / 30.f);

	//Circulo 1
	int numero = 4;
	
	respawnRandomEnemies(random);

	while (window.isOpen())
	{
		sf::Event event;
		elapsed += clock.restart();
		while (elapsed >= update_ms) {
			for (int i = 0; i < enemigos.size(); i++) {		
				enemigos[i]->moveCircle();
			}
			elapsed -= update_ms;
		}
		position = Mouse::getPosition(window);

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			bool leDioTiro = true;

			for (int i = 0; i < enemigos.size(); i++) {
				leDioTiro = Enemigo::checkShotCircle(window, enemigos[i]->ball);
				if (leDioTiro == false) {
					puntaje++;
					enemigos[i]->isDead = true;
				}
			}

			if (yaDisparo == false) {
				if (leDioTiro == false)
					balas -= 1;
				else {
					puntaje += 10;
				}
				yaDisparo = true;
			}

			if (balas == 0) {
				window.close();
				balas = 8;
				enemigos.clear();
			}

			} else {
				shapeDA.setFillColor(Color::Green);
				shapeIA.setFillColor(Color::Green);
				shapeDB.setFillColor(Color::Green);
				shapeIB.setFillColor(Color::Green);

				yaDisparo = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::H)) {

				respawnRandomEnemies(random);
				balas = 7;
			}

			if (verificar_dead() == true) {
				enemigos.clear();
				respawnRandomEnemies(random);
			}
			//respawnRandomEnemies(random);
			num = std::to_string(balas);
			text.setString("Balas:"+num);
			window.clear();
			window.draw(shapeDA);
			window.draw(shapeIA);
			window.draw(shapeDB);
			window.draw(shapeIB);
			window.draw(text);

			num1 = std::to_string(puntaje);
			text1.setString("Puntaje:" + num1);
			window.draw(text1);

			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
				window.close();
			}

			for (int i = 0; i < enemigos.size(); i++) {
				window.draw(enemigos[i]->ball);
			}

			shapeDA.setPosition(position.x+30, position.y);
			shapeDB.setPosition(position.x + 30, position.y - 30);
			shapeIA.setPosition(position.x, position.y);
			shapeIB.setPosition(position.x, position.y-30);
			window.display();
		}
	}


int main(){
	int num = menuOption();

	do {
		if (num == 1) {
			game();
		}

		if (num == 2) {
			puntuacion();
		}
		num = menuOption();
	} while (num != 3);
}

void puntuacion() {
	font.loadFromFile("YARDSALE.ttf");
	Text text;
	text.setFont(font); // font is a sf::Font
	string num1 = std::to_string(puntaje);
	text.setString("Puntuacion maxima: "+num1);
	text.setStyle(sf::Text::Bold);
	text.setPosition(40, 20);

	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML WORK!");
	while (window.isOpen())
	{
		window.clear();
		window.draw(text);
		window.display();
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
			window.close();
		}
	}
}

void setupCircle() {

	shapeDA.setFillColor(sf::Color::Green);
	shapeIA.setFillColor(sf::Color::Green);
	shapeDB.setFillColor(sf::Color::Green);
	shapeIB.setFillColor(sf::Color::Green);

}

void setupFont() {
	if (!font.loadFromFile("YARDSALE.ttf"))
		throw("ERROR LOADING");

	Text text;
	text.setFont(font); // font is a sf::Font
	string num = "8";
	text.setString(num);
	text.setCharacterSize(24); // in pixels, not poin
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	window.draw(text);
}
bool verificar_dead() {
	for (int i = 0; i < enemigos.size(); i++)
	{
		if (enemigos[i]->isDead == false)
			return false;
	}

	return true;
}


void respawnRandomEnemies(std::_Binder < std::_Unforced, std::uniform_int_distribution<int> &, std::reference_wrapper<std::default_random_engine>> random) {
	
	switch (rand() % 5 + 1)
	{
	case 1:
		enemigos.push_back(new Enemigo(random, sf::Color::Green));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		break;
	case 2:
		enemigos.push_back(new Enemigo(random, sf::Color::Green));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		enemigos.push_back(new Enemigo(random, sf::Color::Blue));
		break;
	case 3:
		enemigos.push_back(new Enemigo(random, sf::Color::Green));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		enemigos.push_back(new Enemigo(random, sf::Color::Blue));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		enemigos.push_back(new Enemigo(random, sf::Color::Blue));
		enemigos.push_back(new Enemigo(random, sf::Color::White));
		break;
	case 4:
		enemigos.push_back(new Enemigo(random, sf::Color::White));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		enemigos.push_back(new Enemigo(random, sf::Color::Blue));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		enemigos.push_back(new Enemigo(random, sf::Color::Blue));
		enemigos.push_back(new Enemigo(random, sf::Color::Green));
		enemigos.push_back(new Enemigo(random, sf::Color::Green));
		break;
	case 5:
		enemigos.push_back(new Enemigo(random, sf::Color::Green));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		enemigos.push_back(new Enemigo(random, sf::Color::Blue));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		enemigos.push_back(new Enemigo(random, sf::Color::Yellow));
		break;
	default:
		break;
	}
}
