#include "Entity.h"
#define rmap(a) (int)(((double)a/(double)RAND_MAX)*(double)255)


Entity::Entity(double aradius, double amass, Vector2f aposition, Vector2f velo) {
	radius = aradius;
	vel = velo;
	mass = amass;	
	density = mass / (M_PI * radius * radius);
	entity.setRadius(radius);
	Color c(rmap(rand()), rmap(rand()), rmap(rand()));
	entity.setFillColor(c);
	entity.setOrigin(Vector2f(radius, radius));
	entity.setPosition(aposition);
}

Entity::Entity() {
	radius = 1.0;
	vel = { 0,0 };
	mass = 1.0;
	density = mass / (M_PI * radius * radius);
	entity.setRadius(radius);
	entity.setFillColor(Color(rmap(rand()), rmap(rand()), rmap(rand())));
	entity.setOrigin(Vector2f(radius, radius));
	entity.setPosition(0, 0);
}

Entity::~Entity() {
}

double Entity::getDensity() {
	return density;
}
double Entity::getMass() {
	return mass;
}
double Entity::getRadius() {
	return radius;
}
Vector2f Entity::getVel() {
	return vel;
}
bool Entity::getForces() {
	return forces;
}

void Entity::setDensity(double adensity) {
	density = adensity;
	mass = density * (M_PI * radius * radius);
}
void Entity::setRadius(double aradius) {
	radius = aradius;
	mass = density * (M_PI * radius * radius);
	entity.setRadius(radius);
}
void Entity::setVel(Vector2f avel) {
	vel = avel;
}
void Entity::setForces(bool aforces) {
	forces = aforces;
}

void Entity::draw(RenderWindow& window) {
	window.draw(entity);
}