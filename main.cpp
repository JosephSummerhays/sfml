#include <SFML/Graphics.hpp>
#include <string>
#include <cstdio>
#include <math.h>

#include "joystick.h"
#include "physics.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000,1000), "Hello, World!");
	joystickI* joy = new keyboardJoy(sf::Keyboard::D,
					sf::Keyboard::A,
					sf::Keyboard::S,
					sf::Keyboard::W,
					sf::Keyboard::B,
					sf::Keyboard::C,
					sf::Keyboard::V,
					sf::Keyboard::F);
	controller* c = new controller(joy, sf::Keyboard::LShift, sf::Keyboard::Space);
	player* p = new player("res/p.png", c);
	p->setVelocity(6.6);
	directedWall* w = new directedWall("res/wall.jpg", sf::Vector2f(1,0), sf::IntRect(0,0,4,1000), sf::Vector2f(100,200), true);
	std::vector<player*> players;
	players.push_back(p);
	std::vector<obj*> objects;
	objects.push_back(w);
	objects.push_back(ow);
	objects.push_back(p);
	physicsEngine physics(objects, players);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					//add stuff here
				}
			}
		}
		physics.step(1.0);
		window.clear();
		for (int i = 0; i < objects.size(); i++) {
			window.draw(*(objects.at(i)->getSprite()));
		}
		window.display();
	}

	return 0;
}
