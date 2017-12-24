#include "Player.h"

Player::Player(int ID, int strategyType)
	:m_IDPlayer(ID)
{

}

void Player::insertSoldier(Soldier * s)
{
	m_listSoldier.push_back(s);
}



Human::Human(int ID, int strategyType)
	:Player(ID, strategyType)
{
}

Computer::Computer(int ID ,int strategyType)
	: Player(ID, strategyType)
{

}