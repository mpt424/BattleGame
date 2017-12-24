#include "Strategy.h"
#include "Game.h"
#include <stdlib.h>     /*  rand */
#include <cassert>

using namespace std;
double random::getNewX()
{	
	
	return rand() % int(Field::getWidth());
}
double random::getNewY()
{
	return rand() % int(Field::getHight());
}

double random::getAttackR()
{
	return rand() % (int(Field::getHight() + Field::getWidth()) / 2);
}

double Input::getNewX()
{
	double tempx;
	cout << "Insert new X: " << endl;
	cin >> tempx;
	return tempx;
}

double Input::getNewY()
{
	double tempy;
	cout << "Insert new Y: " << endl;
	cin >> tempy;
	return tempy;
}

double Input::getAttackR()
{
	double R;
	cout << "Insert new Radius: " << endl;
	cin >> R;
	return R;
}

strategy::strategyBuilder::strategyBuilder(int type)
{
	/*There are three strategies*/
	assert(type < 3);

	if (type == RANDOM)
		m_strategyType = RANDOM;
	else if (type == INPUT)
		m_strategyType = INPUT;
	else if (type == IFILE)
		m_strategyType = IFILE;

}