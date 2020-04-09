#include <SFML/Graphics.hpp>
#include <string>
#include <cstdio>

class player {
private:
	sf::Texture* tex;
	sf::Sprite* spir;

public:
	player(std::string im_file) {
		this->tex = new sf::Texture();
		this->spir = new sf::Sprite();
		if(!tex->loadFromFile(im_file)) {
			// error
			fprintf(stderr,"load from file failed\n");
		}
		else {
			tex->setRepeated(false);
			spir->setTexture(*tex);
			fprintf(stderr,"load from file succeeded\n");
		}
	}
	player(sf::Texture* tex) {
		this->tex = tex;
		spir->setTexture(*tex);
	}
	sf::Sprite* getSprite() { return spir; }
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000,1000), "Hello, World!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	player p("res/p.png");

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
		window.clear();
		//window.draw(shape);
		window.draw(*p.getSprite());
		window.display();
	}

	return 0;
}
/*
class w {
private:
	sf::Texture* tex; 
public:
	w(std::string s) {
		tex = new sf::Texture();
		fprintf(stderr, "flag 1");
		if(!tex->loadFromFile(s)) {
			// error
			fprintf(stderr,"load from file failed\n");
		}
		else {
			fprintf(stderr,"load from file succeeded\n");
		}
	}
};
int main() {
	w wut("p.png");
}
*/
