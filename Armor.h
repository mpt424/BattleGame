#include "Object.h"
#include "Point2d.h"


#ifndef  __ARMOR__H
#define __ARMOR__H


class Armor : public Object {

public:
	//Solid(Point2d &p, std::string n, SolidArg & sg);
	Armor(Point2d & p, std::string n, double pow);
	virtual std::string toString();
	double getPower();

private:
	/*ARGUMENT*/
	double m_power;
	bool m_peek;
	bool m_fullBody;

};

#endif	