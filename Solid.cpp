#include "Solid.h"
using namespace std;

/*Solid::Solid(Point2d & p, std::string n, SolidArg & sg)
	: Object(p,n)
{
	*m_argument = sg;
}*/

Solid::Solid(Point2d & p, std::string n, double h, double w)
	: Object(p, n), m_h(h),m_w(w)
{
}

std::string Solid::toString()
{
	return "Solid : "+ m_name +", " + m_point.toString() +
		", <" +  to_string(m_h) + " " + to_string(m_w)+">";
}
