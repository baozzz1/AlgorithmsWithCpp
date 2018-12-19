#pragma once
#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include<queue>
#include<vector>
#include"Particle.h"
class CollisionSystem {
public:
	CollisionSystem(const std::vector<Particle> &particles) :particles(particles) {}
	~CollisionSystem() {}

	void simulate(const double &limit, const double &Hz);

private:
	class Event;
	std::priority_queue<Event> pq;
	double t = 0.0;
	std::vector<Particle> particles;
	void predictCollisions(Particle * const, const double &limit);
};

class CollisionSystem::Event{
	friend class CollisionSystem;
	public:
		Event(const double&, Particle* const, Particle* const);
		const bool isValid() const;
		~Event() {}

		bool operator<(const Event &) const;
		bool operator>(const Event &) const;
	private:
		double time;
		Particle *a, *b;
		int countA, countB;
};

#endif // !COLLISIONSYSTEM_H