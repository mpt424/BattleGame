#include "Game.h"
#include "Soldier.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;
/*==========================================
				CSV reader
=============================================*/

/* read all the values from a csv file
	and return vector with all the values[type strin]*/
 vector<string>* fileReader::getValues(string fileName) throw()
{
		ifstream file(fileName);
		//check if can open the init file else throw exception
		if (!file.is_open()) throw exception("cant open initlaize file");
		vector<string> vec;
		string str((std::istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		//cout << str << endl;
		file.close();	
		vector<string>* v = new vector<string>{ explode(str,'\n',',') };
		return v;
		
	}

 /*convert line to vector of string seperate by 2 delimeters*/
 const std::vector<std::string> fileReader::explode(const std::string & s, const char & c, const char & c2)
 {
	 string buff{ "" };
	 vector<string> v;

	 for (auto n : s)
	 {
		 if (n != c && n != c2) buff += n;
		 else if ((n == c || n == c2) && buff != "") { v.push_back(buff); buff = ""; }
	 }
	 if (buff != "") v.push_back(buff);

	 return v;
 }

 /*convert line to vector of string seperate by 3 delimeters*/
 const std::vector<std::string> fileReader::explode(const std::string & s, const char & c, const char & c2, const char & c3)
 {
	 string buff{ "" };
	 vector<string> v;

	 for (auto n : s)
	 {
		 if (n != c && n != c2 && n != c3) buff += n;
		 else if ((n == c || n == c2 || n == c3) && buff != "") { v.push_back(buff); buff = ""; }
	 }
	 if (buff != "") v.push_back(buff);

	 return v;
 }



 /*====================================================
					GAME CLASS
	====================================================*/
 std::vector<Player*> Game::m_players;


 /* 
 *		this function will init the game by reading values
 *			from from the init file
 *
 */
void Game::initGame(string fileName) throw()
{
	vector<string>* values = fileReader::getValues(fileName);

	int numOfSoldiers = 0;
	int numOfPlayers = 0;
	bool init = false;
	bool initPlayers = false;
	cout << "<<<<<<<<<<<<START INTILAIZE THE GAME>>>>>>>>>>>>>>" << endl;
	for (auto it = values->begin(); it != values->end(); ++it) {
		/*init the field class*/
		if ((*it).compare("battlefieldSize") == 0) {
			++it;
			double width = stod((*it));
			Field::setWidth(width);
			++it;
			double hight = stod((*it));
			Field::setHight(hight);
			cout << "FIELD: " << width << " X " << hight << endl;

		}
		/*get the number of players*/
		if ((*it).compare("players")==0) {
			++it;
			numOfPlayers = stoi((*it));
		}
		/*get the number of soldiers*/
		if ((*it).compare("soldiers") == 0) {
			++it;
			numOfSoldiers = stoi((*it));
			init = true;
			cout << "Number of player: " << numOfPlayers << ", each player has " << numOfSoldiers << " soldiers" << endl;
		}

		/*start init the players and soldiers*/
		if (init && !initPlayers) {
			for (size_t i = 0; i < numOfPlayers; i++)
			{
				++it;
				cout << "\n----Init player " << i+1 << "----" << endl;

				/*init the player itself*/
				Player* p = NULL;
				++it; //pass on the player name
				string type = (*it);

				++it; 
				
				int stategyType = stoi((*it));

				
				/*human player*/
				if (type.compare("human")){
					p = new Human(i, stategyType);
					cout << "   Human player" << endl;
				}
				/*computer player*/
				else {
					p = new Computer(i, stategyType);
					cout << "   Computer player" << endl;
				}

				/*after init the player init the soldiers*/
				for (size_t j = 0; j < numOfSoldiers; j++)
				{
					cout << "\n		init soldier " << j+1 << "...";

					/*soldier type*/
					++it;
					string type = (*it);
					cout << "type: " << type;
					++it;
					/*sodlier start point*/
					const string pointStr = (*it);
					cout << ", possition: " << pointStr;
					vector<string> v = fileReader::explode(pointStr, '[',' ',']');
					double x = stod((v.at(0)));
					double y = stod((v.at(1)));
					Point2d poi(x, y);
					Soldier::SoldierBuilder builder = *Soldier::SoldierBuilder(type, i).point(poi);
					
					/*init soldier weapon if not paramedic*/
					if (type.compare("paramedic") != 0){
						++it;
						string weapon = (*it);
						cout << ", weapon: " << weapon << endl;
						builder.weapon(weapon);
					}

					Soldier* s = builder.build();

					p->insertSoldier(s);

					Field::insertSoldier(s);
				}
			}//done init player
			initPlayers = true;
		}//done init  the players
		

		/*init the objects*/
		if ((*it).compare("Objects") == 0) {

			cout << "Init Objects " << endl;
			++it;
			for (; it != values->end(); ++it) {
				/*the object is weapon*/
				cout << (*it) << " ";

				if ((*it).compare("weapon") == 0) {
					++it;
					string weapon = (*it);
				
					/*weapon start point*/
					++it;
					const string pointStr = (*it);
					vector<string> v = fileReader::explode(pointStr, '[', ' ', ']');
					double x = stod((v.at(0)));
					double y = stod((v.at(1)));
					Point2d poi(x, y);

					Weapon* w = Weapon::WeaponBuilder(weapon).point(poi)->build();
					cout << weapon << " at " << pointStr << endl;
					Field::insertWeapon(w);
				}
				/*the object is armor*/
				else if ((*it).compare("Armor") == 0) {
					++it;
					string name = (*it);

					/*weapon start point*/
					++it;
					const string pointStr = (*it);
					vector<string> v = fileReader::explode(pointStr, '[', ' ', ']');
					double x = stod((v.at(0)));
					double y = stod((v.at(1)));
					Point2d poi(x, y);

					/*armor power*/
					++it;
					const string power = (*it);
					double pow = stod(power);

					Armor* a = new Armor(poi, name, pow);
					cout << name << " with power of " << pow << " at " << pointStr << endl;
					Field::insertArmor(a);
				}
				/*the object is solid*/
				else if ((*it).compare("solid") == 0) {
					++it;
					string name = (*it);

					/*solid start point*/
					++it;
					const string pointStr = (*it);
					vector<string> v = fileReader::explode(pointStr, '[', ' ', ']');
					double x = stod((v.at(0)));
					double y = stod((v.at(1)));
					Point2d poi(x, y);

					/*solid width*/
					++it;
					const string width = (*it);
					double w = stod(width);

					/*solid hight*/
					++it;
					const string hight = (*it);
					double h = stod(hight);

					Solid* s = new Solid(poi, name, w,h);
					cout << name << " width: " << w << " hight: " << h << " at " << pointStr << endl;

					Field::insertSolid(s);
				}
			}//done init object
			break;
		}//done init objects
	}// done pass on the values
	cout << "<<<<<<<<<<Initilaize Done>>>>>>>>>>> " << endl;
}

void Game::startPlay()
{
	cout << " __    _     _  _    __\n" <<
			"/     /_\\   / \\/ \\  |__ \n" <<
			"\\_ ] /   \\ /      \\ |__" << endl;
	/*done present i the game is done*/
	bool done = true;

	/*move on the player list and let him play*/
	for (auto it = m_players.begin(); !done; ++it) {
		/*TODO:current player play*/
		//(*it).play();

		/*TODO: check if some player is dead after the turn
				and remove him fron the list*/

		/*return to the begin of the queue*/
		if (it == m_players.end())
			it = m_players.begin();

		/*TODO:check if the game ended[everybody reach to destenation]
				or there is one winner[all the others player dead
				and end the loop with:
				done = true*/
	} 
}

/*attack method*/
void Game::attack(Soldier &attacker, Soldier &attacked)
{
	/*attack only if there are not at the same army*/
	if (attacker.getPlayerId() != attacked.getPlayerId()) {
		attacker.attack(attacked);
	}
}


void Game::addPlayer(Player * player)
{
	m_players.push_back(player);
}

/*===============================================
			FIELD CLASS
===========================================*/
double Field::m_width = 0;
 double Field::m_hight = 0;
 vector<Weapon*> Field::m_weapons;
 vector<Solid*> Field::m_solids;
 vector<Armor*> Field::m_armors;
 vector<Soldier*> Field::m_soldiers;

void Field::setWidth(double x)
{
	m_width = x;
}

void Field::setHight(double y)
{
	m_hight = y;
}

double Field::getWidth() {
	return m_width;
}
double Field::getHight() {
	return m_hight;
}

void Field::insertWeapon(Weapon * w)
{
	m_weapons.push_back(w);
}

void Field::insertSolid(Solid * s)
{
	m_solids.push_back(s);
}

void Field::insertArmor(Armor * a)
{
	m_armors.push_back(a);
}

void Field::insertSoldier(Soldier * s)
{
	m_soldiers.push_back(s);
}
