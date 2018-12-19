#include<iostream>
#include<iomanip>
#include "CollisionSystem.h"
using namespace std;

CollisionSystem::Event::Event(const double &t, Particle* const a, Particle* const b) :time(t), a(a), b(b) {
	if (a != NULL) countA = a->count();
	else countA = -1;
	if (b != NULL) countB = b->count();
	else countB = -1;
}

const bool CollisionSystem::Event::isValid() const {
	if (a != NULL && a->count() != countA)
		return false;
	if (b != NULL && b->count() != countB)
		return false;
	return true;
}

bool CollisionSystem::Event::operator<(const Event &that) const {
	return this->time > that.time;
}

bool CollisionSystem::Event::operator>(const Event &that) const {
	return *this < that;
}

void CollisionSystem::simulate(const double & limit, const double & Hz) {
	pq = priority_queue<Event>();
	for (int i = 0; i < particles.size(); i++)
		predictCollisions(&particles[i], limit);
	pq.push(Event(0, NULL, NULL));
	while (!pq.empty()) {
		//����һ���¼�
		Event oneEvent = pq.top();
		pq.pop();
		if (!oneEvent.isValid())
			continue;
		for (int i = 0; i < particles.size(); i++)
			particles[i].move(oneEvent.time - t);
		t = oneEvent.time;
		Particle *a = oneEvent.a, *b = oneEvent.b;
		if (a != NULL && b != NULL) {
			a->bounceOff(b);
			//��ӡÿ���¼�����ʱ��������λ��
			cout << "time: " << t << endl;
			cout << "a is ("
				<< setw(6) << a->pos_x() << ", "
				<< setw(6) << a->pos_y() << "), with speed of ("
				<< setw(6) << a->vel_x() << ", "
				<< setw(6) << a->vel_y() << ")." << endl;
			cout << "b is ("
				<< setw(6) << b->pos_x() << ", "
				<< setw(6) << b->pos_y() << "), with speed of ("
				<< setw(6) << b->vel_x() << ", "
				<< setw(6) << b->vel_y() << ")." << endl;
		}
		else if (a != NULL && b == NULL) a->bounceOffVerticalWall();
		else if (a == NULL && b != NULL) b->bounceOffHorizontalWall();
		else if (a == NULL && b == NULL)	;//draw it
		predictCollisions(a, limit);
		predictCollisions(b, limit);
	}
}

//Ԥ���������ӵ���ײ�¼�
void CollisionSystem::predictCollisions(Particle * const a, const double & limit) {
	if (a == NULL) return;
	for (int i = 0; i < particles.size(); i++) {
		//��particles[i]������ײ���¼�����pq��
		double dt = a->timeToHit(&particles[i]);
		if (t + dt <= limit)
			pq.push(Event(t + dt, a, &particles[i]));
	}
	double dtX = a->timeToHitVerticalWall();
	if(t+dtX<=limit)
		pq.push(Event(t + dtX, a, NULL));
	double dtY = a->timeToHitHorizontalWall();
	if (t + dtY <= limit)
		pq.push(Event(t + dtY, NULL, a));
}
