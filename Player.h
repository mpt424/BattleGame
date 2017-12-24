#include <iostream>
#include <list>
#include "Soldier.h"
#include "Strategy.h"
#ifndef  __PLAYER__H
#define __PLAYER__H

class Player {
protected:
	Player(int ID, int strategyType);
	std::list <Soldier*> m_listSoldier;
	int m_IDPlayer;
	int m_numSoldiers;
	strategy *m_stg;

public:
	void insertSoldier(Soldier * s);
	//void play();
};


class Human : public Player {
public:
	Human(int ID, int strategyType);
};

class Computer : public Player {
public:
	Computer(int ID, int strategyType);
};

#endif