#include <SFML/Graphics.hpp>
#include <string>
#include <cstdio>

class player {
private:
	sf::Texture* tex;
	sf::Sprite* spir;

public:
	player(std::string im_file) {
		fprintf(stderr,"flag 1.5\n");
		if(!tex->loadFromFile(im_file)) {
			// error
			tex = NULL;
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
	sf::RenderWindow window(sf::VideoMode(200,200), "Hello, World!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	fprintf(stderr,"flag1\n");
	player p = player("./res/p.png");

	fprintf(stderr,"flag2\n");
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
		fprintf(stderr,"flag3\n");
		window.clear();
		//window.draw(shape);
		window.draw(*p.getSprite());
		fprintf(stderr,"flag4\n");
		window.display();
		fprintf(stderr,"flag5\n");
	}

	return 0;
}
