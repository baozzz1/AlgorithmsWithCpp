#include<iostream>
#include"CollisionSystem.h"
using namespace std;

// Chapter6_0_1_main
int main() {
	int N;
	cin >> N;
	vector<Particle> particles(N);
	CollisionSystem system(particles);
	system.simulate(10000,0.05);
}