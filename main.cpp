#include <SFML/Graphics.hpp>
#include <string>
#include <cstdio>

#include "joystick.h"

class player {
private:
	sf::Texture* tex;
	sf::Sprite* spr;
	controller* c;

public:
	player(std::string im_file, controller* c) {
		this->tex = new sf::Texture();
		this->spr = new sf::Sprite();
		this->c = c;
		if(!tex->loadFromFile(im_file)) {
			// error
			fprintf(stderr,"load from file failed\n");
		}
		else {
			fprintf(stderr,"load from file succeeded\n");
			tex->setRepeated(false);
			spr->setTexture(*tex);
		}
	}
	player(sf::Texture* tex, controller* c) {
		this->tex = tex;
		this->c = c;
		spr->setTexture(*tex);
	}
	void step(float delta) {
		sf::Vector2f x = c->movement();
		fprintf(stderr, "%f %f\n", x.x, x.y);
		spr->move(c->movement()*delta);
	}
	sf::Sprite* getSprite() { return spr; }
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000,1000), "Hello, World!");
	joystickI* joy = new keyboardJoy(sf::Keyboard::A,
					sf::Keyboard::D,
					sf::Keyboard::W,
					sf::Keyboard::S,
					sf::Keyboard::C,
					sf::Keyboard::B,
					sf::Keyboard::F,
					sf::Keyboard::V);
	controller* c = new controller(joy, sf::Keyboard::LShift, sf::Keyboard::Space);
	player p("res/p.png", c);

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
		p.step(1.0);
		window.clear();
		window.draw(*p.getSprite());
		window.display();
	}

	return 0;
}
