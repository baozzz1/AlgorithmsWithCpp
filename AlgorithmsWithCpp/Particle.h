#pragma once
#include<float.h>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<random>
class Particle {
public:
	Particle();
	Particle(const double & rx, const double & ry, const double & vx, const double & vy, const double & s, const double & mass) :
		rx(rx), ry(ry), vx(vx), vy(vy), radius(radius), mass(mass) {}
	//Particle(const Particle &that):
	//void draw() const;
	void move(const double &dt);
	int count() { return _count; }

	double timeToHit(const Particle* const that) const;
	double timeToHitHorizontalWall();
	double timeToHitVerticalWall();
	void bounceOff(Particle* const that);
	void bounceOffHorizontalWall();
	void bounceOffVerticalWall();

	~Particle() {}



private:
	double rx, ry;
	double vx, vy;
	const double radius;
	const double mass;
	int _count;
};

inline Particle::Particle():radius(0.02),mass(0.5) {
	std::default_random_engine e(time(0));
	std::uniform_real_distribution<double> random_r(0.0, 1.0);
	std::uniform_real_distribution<double> random_v(-0.005, 0.005);
	rx = random_r(e);
	ry = random_r(e);
	vx = random_v(e);
	vy = random_v(e);
}

inline void Particle::move(const double &dt) {
	rx += vx * dt;
	ry += vy * dt;
}

inline double Particle::timeToHit(const Particle* const that) const {
	if (this == that) return INFINITY;
	double dx = that->rx - this->rx;
	double dy = that->ry - this->ry;
	double dvx = that->vx - this->vx;
	double dvy = that->vy - this->vy;
	double dvdr = dx * dvx + dy * dvy;
	if (dvdr > 0) return INFINITY;
	double dvdv = dvx * dvx + dvy * dvy;
	if (dvdv == 0) return INFINITY;
	double drdr = dx * dx + dy * dy;
	double sigma = this->radius + that->radius;
	double d = (dvdr*dvdr) - dvdv * (drdr - sigma * sigma);
	// if (drdr < sigma*sigma) println("overlapping particles");
	if (d < 0) return INFINITY;
	return -(dvdr + sqrt(d)) / dvdv;
}

inline double Particle::timeToHitHorizontalWall() {
	if (vy > 0) return (1.0 - ry - radius) / vy;
	else if (vy < 0) return (radius - ry) / vy;
	else             return INFINITY;
}

inline double Particle::timeToHitVerticalWall() {
	if (vx > 0) return (1.0 - rx - radius) / vx;
	else if (vx < 0) return (radius - rx) / vx;
	else             return INFINITY;
}

inline void Particle::bounceOff(Particle* const that) {
	double dx = that->rx - this->rx;
	double dy = that->ry - this->ry;
	double dvx = that->vx - this->vx;
	double dvy = that->vy - this->vy;
	double dvdr = dx * dvx + dy * dvy;             // dv dot dr
	double dist = this->radius + that->radius;   // distance between particle centers at collison

	// magnitude of normal force
	double magnitude = 2 * this->mass * that->mass * dvdr / ((this->mass + that->mass) * dist);

	// normal force, and in x and y directions
	double fx = magnitude * dx / dist;
	double fy = magnitude * dy / dist;

	// update velocities according to normal force
	this->vx += fx / this->mass;
	this->vy += fy / this->mass;
	that->vx -= fx / that->mass;
	that->vy -= fy / that->mass;

	// update collision counts
	this->_count++;
	that->_count++;
}

inline void Particle::bounceOffHorizontalWall() {
	vy = -vy;
	_count++;
}

inline void Particle::bounceOffVerticalWall() {
	vx = -vx;
	_count++;
}
