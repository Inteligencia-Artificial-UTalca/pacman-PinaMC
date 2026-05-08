/*
 * MsPacMan.cpp
 *
 *  Created on: Apr 24, 2018
 *      Author: nbarriga
 */

//Codigo para manejar los stados de pacman en gameState
#include "MsPacMan.h"
#include <iostream>

using namespace std;
extern bool nogui;

MsPacMan::MsPacMan(int startNode):Character(startNode),score(0),lives(3) {
	// TODO Auto-generated constructor stub

}

MsPacMan::~MsPacMan() {
	// TODO Auto-generated destructor stub
}

void MsPacMan::die() {
	Character::die();
	lives--;
	if(!nogui)
		std::cout<<lives<<" lives left!"<<std::endl;
}

void MsPacMan::addScore(int points) {
	score+=points;
	if(!nogui)
		std::cout<<"Score: "<<score<<std::endl;
}

int MsPacMan::getScore()const{
	return score;
}

bool MsPacMan::isDead() const {
	return lives == 0;
}

void MsPacMan::reset(int startNode)
{
	Character::reset(startNode);
	lives = 3;
}
