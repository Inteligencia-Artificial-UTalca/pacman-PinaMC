#include "PinkyController.h"
#include "Controller.h"
#include "BehaviorTree.h"
#include <chrono>

//Implementar controles de Bheaviour tree en PinkyController.cpp
//replicar el codigo base del archivo 
//debe tener las funciones de Frightened, Scatter y Chase, además de las condiciones de Powerpill y TimeOut


PinkyController::PinkyController(std::shared_ptr<Character> character):
	Controller(character){
}

PinkyController::~PinkyController() {

}

Move
PinkyController::getMove(const GameState& game){
	return PASS;	

	
}
