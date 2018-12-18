#pragma once
#include<queue>
#include<vector>
#include"Particle.h"
class CollisionSystem {
public:
	CollisionSystem(const std::vector<Particle> &particles) :particles(particles) {}
	~CollisionSystem() {}


private:
	class Event	{
	public:
		Event(const double &t, const Particle &a, const Particle &b);
		Event(const double & t, const Particle * pa, const Particle * pb);
		const int compareTo(const Event & that) const;
		const bool isValid();
		~Event() {}

	private:
		const double time;
		Particle a, b;
		int countA, countB;
	};

	std::priority_queue<Event> pq;
	double t = 0.0;
	std::vector<Particle> particles;

	void predictCollisions(Particle &a, const double &limit);
};

inline
CollisionSystem::Event::Event(const double &t, const Particle *pa, const Particle *pb) :time(t), a(*pa), b(*pb) {
	if (pa != nullptr) countA = pa->count;
	else countA = -1;
	if (pb != nullptr) countB = pb->count;
	else countB = -1;

}

inline
const int CollisionSystem::Event::compareTo(const Event &that) const {
	if (this->time < that.time)
		return -1;
	else if (this->time > that.time)
		return 1;
	else
		return 0;
}

inline
const bool CollisionSystem::Event::isValid() {
	if (a != nullptr && a.count() != countA)
		return false;
	if (b != nullptr && b.count() != countB)
		return false;
	return true;
}
