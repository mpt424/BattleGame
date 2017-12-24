#include "Object.h"
using namespace std;

Object::Object(Point2d & p, string name)
	: m_point(p.m_x,p.m_y), m_name(name)
{
}
