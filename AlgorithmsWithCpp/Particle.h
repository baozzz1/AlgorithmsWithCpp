#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include<float.h>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<random>

extern std::default_random_engine e;

class Particle {
public:
	Particle();
	//void draw() const;
	void move(const double &dt);
	int count() { return _count; }
	double pos_x()const { return rx; }
	double pos_y()const { return ry; }
	double vel_x()const { return vx; }
	double vel_y()const { return vy; }

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

#endif // !PARTICLE_H