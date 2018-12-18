#pragma once
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
		Event(const Event &one_event){
			Event(one_event.time, one_event.a, one_event.b);
		}
		const bool isValid() const;
		~Event() {}

		bool operator<(const Event* const) const;
		bool operator<(const Event &) const;
		//Event &operator=(const Event &one_event) { *this = Event(one_event); return *this; }
	private:
		double time;
		Particle *a, *b;
		int countA, countB;
};

inline CollisionSystem::Event::Event(const double &t, Particle* const a, Particle* const b) :time(t), a(a), b(b){
	if (a != nullptr) countA = a->count();
	else countA = -1;
	if (b != nullptr) countB = b->count();
	else countB = -1;
}

inline const bool CollisionSystem::Event::isValid() const {
	if (a != nullptr && a->count() != countA)
		return false;
	if (b != nullptr && b->count() != countB)
		return false;
	return true;
}

inline bool CollisionSystem::Event::operator<(const Event * const that) const {
	return this->time < that->time;
}

inline bool CollisionSystem::Event::operator<(const Event &that) const {
	return this->time < that.time;
}