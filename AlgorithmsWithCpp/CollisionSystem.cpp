#include "CollisionSystem.h"

void CollisionSystem::predictCollisions(Particle & a, const double & limit) {
	if (a == nullptr) return;
	for (int i = 0; i < particles.size(); i++) {
		//将particles[i]发生碰撞的事件插入pq中
		double dt = a.timeToHit(particles[i]);
		if (t + dt < limit)
			pq.push(Event(t + dt, a, particles[i]));
	}
	double dtX = a.timeToHitHorizontalWall();
	if(t+dtX<=limit)
		pq.push(Event(t + dtX, a, nullptr));

}
