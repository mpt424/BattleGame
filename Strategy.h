#include <iostream>

#ifndef  __STRATEGY__H
#define __STRATEGY__H

enum StrategyType
{
	RANDOM, IFILE, INPUT
};

class strategy {
public:
	virtual double getNewX() = 0;
	virtual double getNewY() = 0;
	virtual double getAttackR() = 0;

	class strategyBuilder {
	public:
		strategyBuilder(int type);
		StrategyType m_strategyType;
	};
};

class random : public strategy {
	double getNewX();
	double getNewY();
	double getAttackR();
};

class Input : public strategy {
	double getNewX();
	double getNewY();
	double getAttackR();
};

class File : public strategy {

};

#endif