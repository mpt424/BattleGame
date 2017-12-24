#include "Armor.h"
using namespace std;

Armor::Armor(Point2d & p, string n, double pow)
	:Object(p, n), m_power(pow), m_peek(false)
{
	if (n.compare("ShieldArmor") == 0) {
		m_fullBody = true;
	}
	else
		m_fullBody = false;
}

string Armor::toString()
{
	return "Weapon : " + m_name + ", " + m_point.toString()
		+ ", <" + to_string(m_power) + ">";
}

double Armor::getPower()
{
	return m_power;
}
