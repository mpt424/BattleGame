#include "Weapon.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Game.h"

using namespace std;

int main(int argv,char* argc) {

	Game::initGame("init.txt");
	Game::startPlay();
	cin.get();

	return 0;
}