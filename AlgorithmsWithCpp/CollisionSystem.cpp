#include<iostream>
#include "CollisionSystem.h"
using namespace std;
void CollisionSystem::simulate(const double & limit, const double & Hz) {
	pq = priority_queue<Event>();
	for (int i = 0; i < particles.size(); i++)
		predictCollisions(&particles[i], limit);
	pq.push(Event(0, nullptr, nullptr));
	while (!pq.empty()) {
		//处理一个事件
		Event oneEvent = pq.top();
		if (!oneEvent.isValid())
			continue;
		for (int i = 0; i < particles.size(); i++)
			particles[i].move(oneEvent.time - t);
		t = pq.top().time;
		Particle *a = oneEvent.a, *b = oneEvent.b;
		if (a != nullptr && b != nullptr) a->bounceOff(b);
		else if (a != nullptr && b == nullptr) a->bounceOffVerticalWall();
		else if (a == nullptr && b != nullptr) a->bounceOffHorizontalWall();
		else if (a == nullptr && b == nullptr)  ;
		predictCollisions(a, limit);
		predictCollisions(b, limit);

		pq.pop();
		cout << "rua" << endl;
	}
}

//预测其他粒子的碰撞事件
void CollisionSystem::predictCollisions(Particle * const a, const double & limit) {
	if (a == nullptr) return;
	for (int i = 0; i < particles.size(); i++) {
		//将particles[i]发生碰撞的事件插入pq中
		double dt = a->timeToHit(&particles[i]);
		if (t + dt < limit)
			pq.push(Event(t + dt, a, &particles[i]));
	}
	double dtX = a->timeToHitVerticalWall();
	if(t+dtX<=limit)
		pq.push(Event(t + dtX, a, nullptr));
	double dtY = a->timeToHitHorizontalWall();
	if (t + dtY <= limit)
		pq.push(Event(t + dtY, nullptr, a));
}
