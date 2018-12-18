
#include "Particle.h"



Particle::Particle() {
}

Particle::Particle(double rx, double ry, double ux, double uy, double s, double mass)
{
}

void Particle::draw()
{
}

void Particle::move(double dt)
{
}

int Particle::count()
{
	return 0;
}


double Particle::timeToHit(Particle b)
{
	return 0.0;
}

double Particle::timeToHitHorizontalWall()
{
	return 0.0;
}

double Particle::timeToHitVerticalWall()
{
	return 0.0;
}

double Particle::bounceOff(Particle b)
{
	return 0.0;
}

double Particle::bounceOffHorizontalWall()
{
	return 0.0;
}

double Particle::bounceOffVerticalWall()
{
	return 0.0;
}

Particle::~Particle() {
}

const bool Particle::operator==(const Particle &that) const
{
	return false;
}

const bool Particle::operator==(const decltype(nullptr)& null) const
{
	return false;
}

const bool Particle::operator!=(const Particle &that) const
{
	return false;
}

const bool Particle::operator!=(const decltype(nullptr) &null) const
{
	return false;
}
