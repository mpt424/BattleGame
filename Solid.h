#include <string>
#include "Object.h"


#ifndef  __SOLID__H
#define __SOLID__H



class Solid : public Object {

public:
	//Solid(Point2d &p, std::string n, SolidArg & sg);
	Solid(Point2d &p, std::string n, double h, double w);
	virtual std::string toString();

private:
	double m_h;
	double m_w;
};

#endif	