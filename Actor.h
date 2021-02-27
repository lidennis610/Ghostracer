#ifndef ACTOR_H_
#define ACTOR_H_

#include <set>
#include <cmath>
#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject {
public:
	Actor(int imageID, bool valuable, double startX, double startY, StudentWorld* world, int dir, double size, unsigned int depth);

	virtual void doSomething() = 0;
	StudentWorld* getWorld();
	bool getAlive();
	void setAlive(bool set);
	virtual bool isValuable() = 0;
private:
	bool m_isAlive;
	StudentWorld* m_world;
	bool m_valuable;
};

class GhostRacer : public Actor {
public:
	GhostRacer(int imageID, double startX, double startY, StudentWorld* world, double holyWater, double vertSpeed, double hp);
	virtual void doSomething();
	virtual bool isValuable();
	double getVertSpeed();
	void movement();
	int gethp() {
		return m_hp;
	}
private:
	double m_holyWater;
	double m_vertSpeed;
	int m_hp;
	
};
class BorderLine : public Actor {
public:
	BorderLine(int imageID, double startX, double startY, StudentWorld* world, double horzSpeed, double vertSpeed);
	virtual void doSomething();
	virtual bool isValuable();
private:
	double m_horzSpeed;
	double m_vertSpeed;
};
#endif // ACTOR_H_
