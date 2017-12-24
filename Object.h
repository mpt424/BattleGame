#include <string>
#include "Point2d.h"

#ifndef  __OBJECT__H
#define __OBJECT__H



class Object {

public:
	Object(Point2d & p, std::string name);
	virtual std::string toString() = 0;
	Point2d m_point;

protected:
	std::string m_name;
	//Argument *m_argument;
};

#endif	