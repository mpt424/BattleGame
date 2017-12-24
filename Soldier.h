#include <iostream>
#include <list>
#include "Point2d.h"
#include "Armor.h"
#include "Weapon.h"
#include <assert.h>
#include <stdexcept> //for logic exeption

#ifndef  __SOLDIER__H
#define __SOLDIER__H

enum SoldierType {
	NORMAL,PARAMEDIC,SNIPER
};

class Soldier {
public:

 class SoldierBuilder {
	public:
		SoldierBuilder(std::string type, int playerID) throw();
		SoldierBuilder* point(Point2d& point);
		SoldierBuilder* weapon(std::string weapon);
		Soldier* build();

	
	private:
		friend class Soldier;
		SoldierType m_type;
		double m_life;
		Point2d m_point;
		int m_speed;
		double m_attack;
		int m_playerID;
		Armor * m_Shield;
		Armor * m_Body;
		Weapon * m_Weap;
	};

 //double getAttack() const;
	void attack(Soldier & other);
	virtual void changeWeapon(Weapon * weap);
	virtual void fullHeal() = 0;
	Weapon * getWeapon();
	Point2d& getPoint();
	int getPlayerId();
	SoldierType getType();
	virtual void moveTo(double, double) = 0;
	void decreaseLife(Soldier & s);
	virtual double getAttackAbility(double distance) = 0;

protected:
	Soldier(SoldierBuilder* const buider);
	SoldierType m_type;
	double m_life;
	Point2d m_point;
	int m_speed;
	double m_attack;
	int m_playerID;
	Armor * m_Shield;
	Armor * m_Body;
	Weapon * m_Weap;

};

/*===============================================
NORMAL SOLDIER
=================================================*/
class normal :public Soldier {
public:
	void fullHeal();
	double getAttackAbility(double distance);
	
	/*TODO*/
	void moveTo(double, double);
	//void run(double x, double y);

private:
	friend class SoldierBuilder;
	normal(SoldierBuilder* const buider);

};

/*===============================================
PARAMEDIC SOLDIER
=================================================*/
class paramedic :public Soldier {
public:
	void fullHeal();
	void moveTo(double, double);
	double getAttackAbility(double distance);
	void heal(Soldier & other);
	virtual void changeWeapon(Weapon * weap);

private:
	friend class SoldierBuilder;
	paramedic(SoldierBuilder* const buider);

};

/*===============================================
				SNIPER SOLDIER
=================================================*/
class sniper :public Soldier {
public:
	void fullHeal();
	void moveTo(double, double);
	double getAttackAbility(double distance);

private:
	friend class SoldierBuilder;
	sniper(SoldierBuilder* const buider);

};


#endif	