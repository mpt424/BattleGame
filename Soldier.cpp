#include "Soldier.h"
using namespace std;

/*========================================
			SOLDIER BUILDER
===========================================*/

Soldier::SoldierBuilder::SoldierBuilder(std::string type, int playerID)
	: m_point(0, 0) {

	assert(type.length() != 0);

	m_Weap = nullptr;

	if (type.compare("normal") == 0) {
		m_life = 100.0;
		m_speed = 2.0;
		type = NORMAL;
	}
	else if (type.compare("paramedic") == 0) {
		m_life = 120.0;
		m_speed = 4.0;
		type = PARAMEDIC;

	}
	else if (type.compare("sniper") == 0) {
		m_life = 80.0;
		m_speed = 2.0;
		type = SNIPER;

	}
	else {
		throw logic_error("no such a soldier type. try normal/paramedic/sniper...");
	}
}

Soldier::SoldierBuilder * Soldier::SoldierBuilder::point(Point2d & point)
{
	m_point = point;
	return this;
}

Soldier::SoldierBuilder * Soldier::SoldierBuilder::weapon(std::string weapon)
{
	m_Weap = Weapon::WeaponBuilder(weapon).isPeeked(true)->build();
	return this;
}

Soldier * Soldier::SoldierBuilder::build()
{
	switch (m_type) {
		case NORMAL: {
			return new normal(this);
		}
		case PARAMEDIC: {
			return new paramedic(this);
		}
		case SNIPER: {
			return new sniper(this);
		}

	}
	return NULL;
}


/*========================================
			ABSTRACT SOLDIER
===========================================*/
Soldier::Soldier(SoldierBuilder* const builder) :
	m_point(builder->m_point.m_x , builder->m_point.m_y) {
	 m_life = builder->m_life;
	 m_speed = builder->m_speed;
	m_playerID = builder -> m_playerID;
	m_Weap = builder->m_Weap;
	m_type = builder->m_type;
}

void Soldier::attack(Soldier & other)
{
	other.decreaseLife(*this);
}

int Soldier::getPlayerId() {
	return m_playerID;
}

Weapon * Soldier::getWeapon()
{
	return m_Weap;
}

SoldierType Soldier::getType() {
	return m_type;
}

Point2d& Soldier::getPoint() {
	return m_point;
}

/*this func get the attacker soldier and decrease the attacked
soldier life by the attacker weapon type
and the attacked armors types*/
void Soldier::decreaseLife(Soldier & s)
{	
	double distance = m_point.distance(s.getPoint());
	double attackAbility = s.getAttackAbility(distance);
	/*check if the attacker weapon is a missile*/
	if (s.getWeapon()->getType() != weapontype::MISSILE  ) {
		/*attacked has body and shield armor*/
		if(m_Body != nullptr && m_Shield != nullptr)
		m_life -= m_Body->getPower() * m_Shield->getPower() * attackAbility;
		/*attacked has only shield armor*/
		else if(m_Body == nullptr && m_Shield != nullptr)
			m_life -= m_Shield->getPower() * attackAbility;
		/*attacked has only body armor*/
		else if (m_Body != nullptr && m_Shield == nullptr)
			m_life -= m_Body->getPower() * attackAbility;
		/*no armor*/
		else
			m_life -= attackAbility;
	}
	/*if the attacker weapon is a missile*/
	else {
		/*only shield armor effective in this case*/
		if (m_Shield != nullptr)
			m_life -= m_Shield->getPower() * attackAbility;
		/*no armor (or just body - not effective against missile*/
		else
			m_life -= attackAbility;
	}
}

/*replace the weapon of the soldier*/
void Soldier::changeWeapon(Weapon* weap) {
	if (m_Weap != nullptr) {
		m_Weap->m_point = m_point;
		m_Weap->m_peek = false;
	}
	m_Weap = weap;
	m_Weap->m_peek = true;
}


/*===============================================
			NORMAL SOLDIER
=================================================*/
normal::normal(SoldierBuilder * const builder) :Soldier(builder)
{
}

void normal::fullHeal()
{
	m_life = 100;
}
void normal::moveTo(double x, double y)
{
	
}
double normal::getAttackAbility(double distance)
{
	return (1 / distance);
}
void run(double x, double y)
{
}

/*===============================================
NORMAL PARAMEDIC
=================================================*/
paramedic::paramedic(SoldierBuilder * const builder) :Soldier(builder)
{
}

void paramedic::fullHeal()
{
	m_life = 120;
}

void paramedic::moveTo(double x, double y)
{

}

double paramedic::getAttackAbility(double distance)
{
	if (distance > 0)return 0;
	return 10;
}

void paramedic::heal(Soldier & other)
{
	other.fullHeal();
}

void  paramedic::changeWeapon(Weapon * weap)
{
	cout << "paramedic can't peek weapon" << endl;
}

/*===============================================
NORMAL SOLDIER
=================================================*/
sniper::sniper(SoldierBuilder * const builder) :Soldier(builder)
{
}

void sniper::fullHeal()
{
	m_life = 80;
}

void sniper::moveTo(double x, double y)
{

}

double sniper::getAttackAbility(double distance)
{
	return ((distance - 1) / distance);
}
