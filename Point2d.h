#include <iostream>
#include <list>
#include <string>

#ifndef  __POINT2D__H
#define __POINT2D__H



class Point2d {
public:
	Point2d(double x, double y);
	double m_x;
	double m_y;

	double distance(Point2d const &)const;
	std::string toString()const;
};

#endif	