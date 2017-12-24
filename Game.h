#include "Soldier.h"
#include <vector>
#include <string>
#include "Solid.h"
#include "Player.h"

class Field {
public:
	static void setWidth(double x);
	static void setHight(double y);
	static double getWidth();
	static double getHight();
	static void insertWeapon(Weapon*);
	static void insertSolid(Solid*);
	static void insertArmor(Armor*);
	static void insertSoldier(Soldier*);
	//static Soldier& getTheClosetSoldierAtRadius(Point2d& myPoint, double radius);
	//static void printGameStatus();

private:
	static double m_width;
	static double m_hight;
	static std::vector<Weapon*> m_weapons;
	static std::vector<Solid*> m_solids;
	static std::vector<Armor*> m_armors;
	static std::vector<Soldier*> m_soldiers;


	

};

class Game {
public:
	static void initGame(std::string fileName) throw();
	static void startPlay();
	/*void moveSoldierTo(Soldier&, double, double);*/
	void attack(Soldier&, Soldier&);
	static void addPlayer(Player*);


private:
	static std::vector<Player*> m_players;


};

class fileReader {
public:
	static std::vector<std::string>* getValues(std::string fileName) throw();
	static const std::vector<std::string> explode(const std::string& s, const char& c, const char& c2);
	static const std::vector<std::string> explode(const std::string& s, const char& c, const char& c2, const char& c3);
	//static bool writeToCsvFile(std::string fileName);


};
