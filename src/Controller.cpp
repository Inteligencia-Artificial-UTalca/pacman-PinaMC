/*
 * Character.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: VIDEOJUEGOS UTALCA
 */
//Este codigo sirve para definir el comportamiento de los personajes del juego, tanto pacman como los fantasmas. 
//El controlador es el encargado de decidir que movimiento realizar en cada momento, y se pueden implementar diferentes
// estrategias para cada personaje. En este caso, se implementa un controlador basado en una máquina de estados finitos (FSMController)
// que cambia de estado dependiendo de la cantidad de pastillas restantes en el juego.
#include "Character.h"
#include "Controller.h"
#include <iostream>
Controller::Controller(std::shared_ptr<Character> _character):character(_character) {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

Move Controller::getMove(const GameState&) {
	//std::cerr<<"controller getmove \n";
	return PASS;
}
float euclid2(std::pair<int,int> a,std::pair<int,int> b){
	return (a.first-b.first)*(a.first-b.first) +(a.second-b.second)*(a.second-b.second);
}