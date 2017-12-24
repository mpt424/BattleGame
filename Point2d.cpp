#include "Point2d.h"
#include <math.h>
using namespace std;

Point2d::Point2d(double x = 0, double y = 0) : m_x(x) , m_y(y)
{
}

std::string Point2d::toString() const
{
	return "[" + to_string(m_x) + " " + to_string(m_y) +"]";
}

double Point2d::distance(Point2d const & p)const
{
	return sqrt(pow(this->m_x - p.m_x, 2) + pow(this->m_y - p.m_y, 2));
}
