#include "Actor.h"
#include "StudentWorld.h"
#include"GameWorld.h"
#include<cmath>
#include<math.h>
# define M_PI           3.14159265358979323846  /* pi */
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int imageID, bool valuable, double startX, double startY, StudentWorld* world, int dir, double size, unsigned int depth):
		GraphObject(imageID, startX, startY, dir, size, depth)
		{
	m_world = world;
	m_isAlive = true;

	}

StudentWorld* Actor::getWorld() {
	return this->m_world;
}
bool Actor::getAlive() {
	return m_isAlive;
}
void Actor::setAlive(bool set) {
	m_isAlive = set;
}
GhostRacer::GhostRacer(int imageID, double startX, double startY, StudentWorld* world, double holyWater, double vertSpeed, double hp) : Actor(IID_GHOST_RACER, true, startX, startY, world, 90, 4.0, 0) {
	m_holyWater = 10;
	m_vertSpeed = 0;
	m_hp = 100;
}
bool GhostRacer::isValuable() {
	return true;
}
double GhostRacer::getVertSpeed() {
	return m_vertSpeed;
}
void GhostRacer::movement() {
	double max_shift_per_tick = 4.0;
	double direction = getDirection();
	double delta_x = cos(direction * (M_PI / 180)) * max_shift_per_tick;
	double cur_x = getX();
	double cur_y = getY();
	moveTo(cur_x + delta_x, cur_y);
}
void GhostRacer:: doSomething() {
		if (m_hp <= 0) { // #1
			return;
		}
		int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH / 2;
    int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH / 2;
		if (getX() <= LEFT_EDGE) { //#2
			if (getDirection() > 90) {
				m_hp -= 10;
				if (m_hp <= 0) {
					setAlive(false);
					getWorld()->playSound(SOUND_PLAYER_DIE);
				}
				setDirection(82);
				getWorld()->playSound(SOUND_VEHICLE_CRASH);
				movement();//step 5
				
			}
		}

		if (getX() >= RIGHT_EDGE) { //#3
			if (getDirection() < 90) {
				m_hp -= 10;
				if (m_hp <= 0) {
					setAlive(false);
					getWorld()->playSound(SOUND_PLAYER_DIE);
				}
				setDirection(98);
				getWorld()->playSound(SOUND_VEHICLE_CRASH);
				movement();//step 5
				
			}
		}

		int ch = 0; // #4
		if (getWorld()->getKey(ch)) {
			if (ch == KEY_PRESS_LEFT && getDirection() < 114) {
				setDirection(getDirection() + 8);
				movement();//step 5
			}
			if (ch == KEY_PRESS_RIGHT && getDirection() > 66) {
				setDirection(getDirection() - 8);
				movement();//step 5
			}
			if (ch == KEY_PRESS_UP && getVertSpeed() < 5) {
				m_vertSpeed += 1;
				movement();//step 5
			}
			if (ch == KEY_PRESS_DOWN && getVertSpeed() > -1) {
				if (m_vertSpeed > 0) {
					m_vertSpeed -= 1;
				}
				
				movement();//step 5
			}
			//if (ch == KEY_PRESS_SPACE) {
				//Introduce a new holy water spray object in front of
				//me, with an angle matching my angle
			//}

		}
		movement();
}

BorderLine::BorderLine(int imageID, double startX, double startY, StudentWorld* world, double horzSpeed, double vertSpeed) : Actor(imageID, false, startX, startY, world, 0, 2, 2) {
	
	m_horzSpeed = horzSpeed;
	m_vertSpeed = vertSpeed;
}
bool BorderLine::isValuable() {
	return false;
}
void BorderLine::doSomething() {
	double vert_speed = m_vertSpeed - getWorld()->getGR()->getVertSpeed();
	double horiz_speed = m_horzSpeed;
	double new_y = getY() + vert_speed;
	double new_x = getX() + horiz_speed;
	moveTo(new_x, new_y);
	if (getX() < 0 || getY() < 0 || getX() > VIEW_WIDTH || getY() > VIEW_HEIGHT) {
		setAlive(false);
		return;
	}
}