#include "CollisionSystem.h"

void CollisionSystem::predictCollisions(Particle & a, const double & limit) {
	if (a == nullptr) return;
	for (int i = 0; i < particles.size(); i++) {
		//��particles[i]������ײ���¼�����pq��
		double dt = a.timeToHit(particles[i]);
		if (t + dt < limit)
			pq.push(Event(t + dt, a, particles[i]));
	}
	double dtX = a.timeToHitHorizontalWall();
	if(t+dtX<=limit)
		pq.push(Event(t + dtX, a, nullptr));

}
