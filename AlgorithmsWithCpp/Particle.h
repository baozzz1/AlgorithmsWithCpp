#pragma once
class Particle {
public:
	Particle();
	Particle(double rx,double ry,
		double ux, double uy,
		double s,
		double mass);
	void draw();
	void move(double dt);
	int count();

	double timeToHit(Particle b);
	double timeToHitHorizontalWall();
	double timeToHitVerticalWall();
	double bounceOff(Particle b);
	double bounceOffHorizontalWall();
	double bounceOffVerticalWall();

	~Particle();

	const bool operator==(const Particle &that) const;
	const bool operator==(const decltype(nullptr) &null) const;
	const bool operator!=(const Particle &that) const;
	const bool operator!=(const decltype(nullptr) &null) const;
};

