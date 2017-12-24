#include "Weapon.h"
#include <stdexcept> 

using namespace std;

/*======================================
			WEAPON BUILDER
======================================*/

/*build weapon with type and num of bullets by the given name
		*/

Weapon::WeaponBuilder::WeaponBuilder(std::string n) throw ()
:m_point(0,0),m_peek(false){
	if (n.compare("UZI") == 0) {
		m_numBullets = 3;
		type = UZI;
		m_power = 40;
		m_name = "UZI";
	}
	else if (n.compare("M16")==0 || n.compare("Missile")==0) {
		m_numBullets = 1;
		if (n.compare("M16") == 0) {
			type = M16;
			m_power = 50;
			m_name = "M16";

		}
		else {
			type = MISSILE;
			m_power = 100;
			m_name = "Missile";

		}
	}
	else
	{
		throw logic_error("There is not such a weapon. try UZI/M16/Missile");
	}

}

/*init point*/
Weapon::WeaponBuilder* Weapon::WeaponBuilder::point(Point2d & p) {
	m_point = p;
	return this;
}

/*init peeked*/
Weapon::WeaponBuilder* Weapon::WeaponBuilder::isPeeked(bool peek) {
	m_peek = peek;
	return this;
}

/*return the final weapon*/
Weapon* Weapon::WeaponBuilder::build() {
	return new Weapon(this);
}

/*==================================================
				WEAPON
=================================================*/

Weapon::Weapon(Weapon::WeaponBuilder* const builder )
	:Object(builder->m_point, builder->m_name) , m_power(builder->m_power), m_peek(builder->m_peek)
{
	
}

string Weapon::toString()
{
	return "Weapon : " + m_name + ", " + m_point.toString() 
		+ ", <" + to_string(m_power) + ">";
}

weapontype Weapon::getType()
{
	if (m_name.compare("M16"))
		return M16;
	else if (m_name.compare("UZI"))
		return UZI;
	else
		return MISSILE;
}


