#include "Object.h"
#include "Point2d.h"
#include <stdexcept> //for logic exeption


#ifndef  __WEAPON__H
#define __WEAPON__H
enum weapontype{ M16, UZI, MISSILE };



class Weapon : public Object {
public:

	/*iner class builder*/
	class WeaponBuilder {
	public:
		WeaponBuilder(std::string n) throw ();
		WeaponBuilder* point(Point2d & p);
		WeaponBuilder* isPeeked(bool peek);
		Weapon* build();

	private:
		friend class Weapon;
		/*ARGUMENT*/
		double m_power;
		bool m_peek;
		int m_numBullets;
		weapontype type;
		Point2d m_point;
		std::string m_name;
	};

	
	virtual std::string toString();
	weapontype getType();
	double getPower();
	bool isPeeked();
	int getNumOfBullets();
	bool m_peek;

private:
	Weapon(WeaponBuilder* builder)throw();
	
	/*ARGUMENT*/
	double m_power;
	int m_munBullets;
	
};







#endif	