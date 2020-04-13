#include "Collision.h"
#include "joystick.h"


inline float dot(sf::Vector2f u, sf::Vector2f v) {
	return u.x*v.x+u.y*v.y;
}
inline float len(sf::Vector2f v) {
	return sqrt(dot(v,v));
}
inline void norm(sf::Vector2f& v) {
	v = v/len(v);
}

class obj {
private:
	sf::Texture* tex;
	sf::Sprite* spr;
public:
	obj(std::string im_file, bool repeat=false) {
		tex = new sf::Texture();
		Collision::CreateTextureAndBitmask(*tex, im_file);
		tex->setRepeated(repeat);
		spr = new sf::Sprite();
		spr->setTexture(*tex);
	}
	obj(sf::Texture* &tex) {
		this->tex = tex;
		spr = new sf::Sprite();
		spr->setTexture(*tex);
	}
	obj(std::string &im_file, sf::IntRect &box, bool repeat=false) : obj(im_file, repeat){
		Collision::CreateTextureAndBitmask(*tex, im_file);
		tex->setRepeated(repeat);
		spr = new sf::Sprite();
		spr->setTexture(*tex);
		spr->setTextureRect(box);
	}
	obj(std::string &im_file, sf::IntRect &box, sf::Vector2f initialPosition, bool repeat=false) : obj(im_file,box,repeat){
		spr->move(initialPosition);
	}
	obj(sf::Texture* &tex, sf::IntRect &box) : obj(tex){
		spr->setTextureRect(box);
	}
	obj(sf::Texture* &tex, sf::IntRect &box, sf::Vector2f initialPosition) : obj(tex,box) {
		spr->move(initialPosition);
	}
	sf::Texture* getTex() { return tex; }
	sf::Sprite* getSprite() { return spr; }
	virtual sf::Vector2f getNormal(sf::Vector2f movement, sf::Vector2f position) {
		return sf::Vector2f(0,0);
	}
};

class directedWall : public obj {
private:
	sf::Vector2f normal;
public:
	directedWall(std::string im_file, sf::Vector2f normal,sf::IntRect box, bool repeat=false) : obj(im_file,box, repeat) {
		this->normal = normal;
		norm(this->normal);
	}
	directedWall(sf::Texture* tex, sf::Vector2f normal, sf::IntRect box) : obj(tex,box) {
		this->normal = normal;
		norm(this->normal);
	}
	directedWall(std::string im_file, sf::Vector2f normal, sf::IntRect box, sf::Vector2f initialPosition, bool repeat=false) : obj(im_file,box,initialPosition, repeat) {
		this->normal = normal;
		norm(this->normal);
	}
	sf::Vector2f getNormal(sf::Vector2f movement, sf::Vector2f position) {
		float component = dot(movement, normal);
		return abs(component)*normal; // no need to normalize normal, (it's already normalized in constructor)
	}
};

class omniWall : public obj {
public:
	omniWall(std::string im_file, sf::IntRect box) : obj(im_file, box, true) {
	}
	omniWall(sf::Texture* tex, sf::IntRect box) : obj(tex, box) {
	}
	sf::Vector2f getNormal(sf::Vector2f movement, sf::Vector2f position) {
		sf::Vector2f normal = position;
		norm(normal);
		float component = dot(movement, normal);
		return normal*abs(component);
	}
};

class player: public obj {
private:
	controller* c;
	float velocity = 1;
	sf::Vector2f movement;
	friend class physicsEngine;
public:
	player(std::string im_file, controller* c):obj(im_file) {
		this->c = c;
	}
	player(sf::Texture* tex, controller* c):obj(tex) {
		this->c = c;
	}
	void setVelocity(float v) {
		velocity = v;
	}

	sf::Vector2f startMovementVector(float delta) {
		sf::Vector2f x = c->movement();
		return c->movement()*delta*velocity;
	}
	void interact(obj o) {
	}
	void step() {
		getSprite()->move(movement);
	}
};

class physicsEngine {
	std::vector<obj*> scene;
	std::vector<player*> players;
public:
	physicsEngine(std::vector<obj*> scene, std::vector<player*> players) {
		this->scene = scene;
		this->players = players;
	}
	void step(float delta) {
		const sf::Uint8 alphaLevel = 1;
		for (int i = 0; i < players.size(); i++) {
			player* p = players.at(i);
			p->movement = p->startMovementVector(delta);
			for (int j = 0; j < scene.size(); j++) {
				obj* o = scene.at(j);
				if (p != o) {
					if (Collision::PixelPerfectTest(*p->getSprite(),*o->getSprite(), alphaLevel)) {
						fprintf(stderr, "Collision detected\n");
						p->interact(*o);
						fprintf(stderr, "movement pre: %f %f\n", p->movement.x, p->movement.y);
						p->movement += o->getNormal(p->movement,Collision::GetSpriteCenter(*(p->getSprite())));
						fprintf(stderr, "movement post: %f %f\n", p->movement.x, p->movement.y);

					}
				}
			}
		}
		for (int i = 0; i < players.size(); i++) {
			players.at(i)->step();
		}
	}
};
