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

#define ScreenWidth 1000
#define ScreenHeight 400
using namespace sf;
using namespace std;

RenderWindow window(VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
RectangleShape *rectangle = new RectangleShape();
RectangleShape *rectangle1 = new RectangleShape();
RectangleShape *ball = new RectangleShape();
RectangleShape *ball2 = new RectangleShape();
CircleShape shape(10.f);
Font font;

Texture texture;

bool isDead = false, isDead1 = false;


bool yaDisparo = false;

const int window_width = 1000;
const int window_height = 400;
const float ball_radius = 30.f;
const int bpp = 32;


int balas = 7;
int puntaje = 0;

void setupRectangle();
void setupCircle();
void setupFont();
void crearPelota();
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
						std::cout << "Play button has been pressed" << std::endl;
						return 1;
						break;
					case 2:
						std::cout << "Option button has been pressed" << std::endl;
						return 2;
						break;
					case 3:
						window.close();
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
	setupRectangle();
	setupCircle();
	setupFont();

	Vector2i position = Mouse::getPosition(window); //sf::Mouse::setPosition(sf::Vector2i(100, 200), window); 
	window.setMouseCursorVisible(false);
	//window.setVerticalSyncEnabled(true);

	std::random_device seed_device;
	std::default_random_engine engine(seed_device());
	std::uniform_int_distribution<int> distribution(-16, 16);

	//Valores random para el movement
	auto random = std::bind(distribution, std::ref(engine));
	auto random1 = std::bind(distribution, std::ref(engine));

	//Direccion random
	sf::Vector2f direction(random(), random());
	const float velocity = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	sf::Vector2f direction1(random1(), random1());
	const float velocity1 = std::sqrt(direction1.x * direction1.x + direction1.y * direction1.y);

	Enemigo enemy(sf::Color::White, 0, 0, rectangle);
	Enemigo enemy1(sf::Color::Red, 60, 0, rectangle1);

	sf::Clock clock;
	sf::Time elapsed = clock.restart();
	const sf::Time update_ms = sf::seconds(1.f / 30.f);

	//Circulo 1
	sf::CircleShape ball(ball_radius - 4);
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::Yellow);
	ball.setOrigin(ball_radius / 2, ball_radius / 2);
	ball.setPosition(window_width / 2, window_height / 2);

	//Circulo 2
	sf::CircleShape ball2(ball_radius - 4);
	ball.setOutlineThickness(6);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::Blue);
	ball.setOrigin(ball_radius / 4, ball_radius / 4);
	ball.setPosition(window_width / 4, window_height / 4);



	while (window.isOpen())
	{
		enemy.move(rectangle);
		enemy1.move(rectangle1);
		sf::Event event;

		
			///////////
			elapsed += clock.restart();
			while (elapsed >= update_ms) {
				//cout << "entra";
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

				const auto pos2 = ball2.getPosition();
				const auto delta2 = update_ms.asSeconds() * velocity1;
				sf::Vector2f new_pos1(pos2.x + direction1.x * delta2, pos2.y + direction1.y * delta2);

				if (new_pos1.x - ball_radius < 0) { // Izquierda
					direction1.x *= -1;
					new_pos1.x = 0 + ball_radius;
				} else if (new_pos1.x + ball_radius >= window_width) { // Derecha
					direction1.x *= -1;
					new_pos1.x = window_width - ball_radius;
				} else if (new_pos1.y - ball_radius < 0) { // Arriba
					direction1.y *= -1;
					new_pos1.y = 0 + ball_radius;
				} else if (new_pos1.y + ball_radius >= window_height) { // Fondo
					direction1.y *= -1;
					new_pos1.y = window_height - ball_radius;
				}
				ball2.setPosition(new_pos1);

				elapsed -= update_ms;
			}

			//cout << "entra";

			position = Mouse::getPosition(window);

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				isDead = enemy.checkShot(window, shape, rectangle);
				isDead1 = enemy1.checkShot(window, shape, rectangle1);
				bool leDioTiro = Enemigo::checkShotCircle(window, ball);
				bool otroTiro = false;
				if (leDioTiro == false)
					otroTiro = Enemigo::checkShotCircle(window, ball2);

				if (yaDisparo == false) {
					if (leDioTiro == false)
						balas -= 1;
					else {
						puntaje += 10;
						cout << puntaje << endl;
					}


					if (otroTiro == true) {
						puntaje += 10;
						cout << puntaje << endl;
					}

					yaDisparo = true;
				}



				if (balas == 0)
					window.close();



			} else {
				shape.setFillColor(Color::Green);
				enemy.alreadyHit = false;
				enemy1.alreadyHit = false;
				yaDisparo = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::H)) {
				rectangle->setPosition(10, 20);
				rectangle1->setPosition(50, 50);
				ball.setFillColor(Color::Blue);
				ball2.setFillColor(Color::Yellow);
				balas = 7;

				if (enemy.isDead == true)
					enemy.restart();
				if (enemy1.isDead == true)
					enemy1.restart();
			}
			window.clear();


			/*if (isDead == false)
			window.draw(*rectangle);

			if (isDead1 == false)
			window.draw(*rectangle1);*/
			window.draw(shape);
			window.draw(ball);
			window.draw(ball2);
			shape.setPosition(position.x, position.y);
			window.display();
		}



	}


int main()
{
	int num = menuOption();

	/*texture.loadFromFile("images.jpg");
	Sprite backg(texture);*/
	if (num == 1) {
		game();
	}
}
void setupRectangle() {
	rectangle->setSize(sf::Vector2f(100, 50));
	/*rectangle.setOutlineColor(sf::Color::Red);*/
	rectangle->setOutlineThickness(2);
	rectangle->setPosition(10, 20);

}

void crearPelota() {
	const int window_width = 1000;
	const int window_height = 400;
	const float ball_radius = 30.f;

	sf::CircleShape ball(ball_radius - 4);
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setFillColor(sf::Color::Yellow);
	ball.setOrigin(ball_radius / 2, ball_radius / 2);
	ball.setPosition(window_width / 2, window_height / 2);
	window.draw(ball);
}

//void moverPelota() {
//	sf::Clock clock;
//	sf::Time elapsed = clock.restart();
//	const sf::Time update_ms = sf::seconds(1.f / 30.f);
//
//	while (elapsed >= update_ms) {
//		const auto pos = ball.getPosition();
//		const auto delta = update_ms.asSeconds() * velocity;
//		sf::Vector2f new_pos(pos.x + direction.x * delta, pos.y + direction.y * delta);
//
//		if (new_pos.x - ball_radius < 0) { // left window edge
//			direction.x *= -1;
//			new_pos.x = 0 + ball_radius;
//		} else if (new_pos.x + ball_radius >= window_width) { // right window edge
//			direction.x *= -1;
//			new_pos.x = window_width - ball_radius;
//		} else if (new_pos.y - ball_radius < 0) { // top of window
//			direction.y *= -1;
//			new_pos.y = 0 + ball_radius;
//		} else if (new_pos.y + ball_radius >= window_height) { // bottom of window
//			direction.y *= -1;
//			new_pos.y = window_height - ball_radius;
//		}
//		ball.setPosition(new_pos);
//
//		elapsed -= update_ms;
//	}
//}

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

//void crearPelota() {
//	const int window_width = 400;
//	const int window_height = 300;
//	const float ball_radius = 16.f;
//	//const int bpp = 32;
//
//	RectangleShape *rect = new RectangleShape();
//	setupRectangle(rect);
//
//
//	window.draw(ball);
//}

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