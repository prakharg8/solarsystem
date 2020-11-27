#pragma once

#define _USE_MATH_DEFINES
#ifndef Entity_H
#define Entity_H
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Network.hpp"
#include "SFML\Audio.hpp"

using namespace sf;
using namespace std;

class Entity {
private:
	double density;
	double mass;
	double radius;
	Vector2f vel;
	bool forces = false;
public:
	CircleShape entity;
	Entity(double aradius, double amass, Vector2f aposition, Vector2f velo);
	Entity();
	~Entity();

	double getDensity();
	double getMass();
	double getRadius();
	Vector2f getVel();
	bool getForces();

	void setDensity(double adensity);
	void setRadius(double aradius);
	void setVel(Vector2f avel);
	void setForces(bool aforces);

	void draw(RenderWindow& window);
};

#endif
