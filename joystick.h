#ifndef JOYSTICK_H
#define JOYSTICK_H
#include <SFML/Graphics.hpp>
#include <math.h>

class joystickI {
public:
	virtual sf::Vector2f getXY() = 0;
	virtual sf::Vector2f getZR() = 0;
};

class joystick : public joystickI {
private:
	short joyNum;
public:
	joystick(short joyNum) {
		this->joyNum = joyNum;
	}
	float getXAxis() {
		return sf::Joystick::getAxisPosition(joyNum, sf::Joystick::X);
	}
	float getYAxis() {
		return sf::Joystick::getAxisPosition(joyNum, sf::Joystick::Y);
	}
	float getZAxis() {
		return sf::Joystick::getAxisPosition(joyNum, sf::Joystick::Z);
	}
	float getRAxis() {
		return sf::Joystick::getAxisPosition(joyNum, sf::Joystick::R);
	}
	sf::Vector2f getXY() {
		return sf::Vector2f(getXAxis(),getYAxis());
	}
	sf::Vector2f getZR() {
		return sf::Vector2f(getZAxis(),getRAxis());
	}
};

class keyboardJoy : public joystickI {
private:
	sf::Keyboard::Key XPos;
	sf::Keyboard::Key XNeg;
	sf::Keyboard::Key YPos;
	sf::Keyboard::Key YNeg;

	sf::Keyboard::Key ZPos;
	sf::Keyboard::Key ZNeg;
	sf::Keyboard::Key RPos;
	sf::Keyboard::Key RNeg;
public:
	keyboardJoy(sf::Keyboard::Key XPos,
			sf::Keyboard::Key XNeg,
			sf::Keyboard::Key YPos,
			sf::Keyboard::Key YNeg,
			sf::Keyboard::Key ZPos,
			sf::Keyboard::Key ZNeg,
			sf::Keyboard::Key RPos,
			sf::Keyboard::Key RNeg) {
		this->XPos = XPos;
		this->XNeg = XNeg;
		this->YPos = YPos;
		this->YNeg = YNeg;
		this->ZPos = ZPos;
		this->ZNeg = ZNeg;
		this->RPos = RPos;
		this->RNeg = RNeg;
	}
	sf::Vector2f getXY();
	sf::Vector2f getZR();
};

sf::Vector2f keyboardJoy::getXY() {
	short xp = sf::Keyboard::isKeyPressed(XPos);
	short xn = sf::Keyboard::isKeyPressed(XNeg);
	short yp = sf::Keyboard::isKeyPressed(YPos);
	short yn = sf::Keyboard::isKeyPressed(YNeg);
	float x = xp-xn;
	float y = yp-yn;
	float denom = sqrt(x*x + y*y); // normalize
	if (denom == 0.0) { denom = 1; }
	return sf::Vector2f(x,y)/denom;

}
sf::Vector2f keyboardJoy::getZR() {
	short zp = sf::Keyboard::isKeyPressed(ZPos);
	short zn = sf::Keyboard::isKeyPressed(ZNeg);
	short rp = sf::Keyboard::isKeyPressed(RPos);
	short rn = sf::Keyboard::isKeyPressed(RNeg);
	float z = zp-zn;
	float r = rp-rn;
	float denom = sqrt(z*z + r*r);
	if (denom == 0.0) { denom = 1; }
	return sf::Vector2f(z,r)/denom;

}

class controller {
private:
	sf::Keyboard::Key fire;
	sf::Keyboard::Key action;
	joystickI* joy;
public:
	controller(joystickI* joy, sf::Keyboard::Key fire, sf::Keyboard::Key action) {
		this->joy = joy;
		this->fire = fire;
		this->action = action;
	}
	bool isFire() {
		return sf::Keyboard::isKeyPressed(fire);
	}
	bool isAction() {
		return sf::Keyboard::isKeyPressed(action);
	}
	sf::Vector2f movement() {
		return joy->getXY();
	}
	sf::Vector2f aim() {
		return joy->getZR();
	}
};
#endif
