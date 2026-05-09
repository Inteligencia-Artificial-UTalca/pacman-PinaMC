#include "PinkyController.h"
#include "Controller.h"
#include "BehaviorTree.h"
#include <chrono>

//Implementar controles de Bheaviour tree en PinkyController.cpp
//replicar el codigo base del archivo 
//debe tener las funciones de Frightened, Scatter y Chase, además de las condiciones de Powerpill y TimeOut

//Este fantasma intenta alcanzar a Pac moviéndose paralelo a él.
PinkyController::PinkyController(std::shared_ptr<Character> character):
	Controller(character), root(std::make_shared<Selector>())  {
	
	//crear comportamiento de pinky usando de base el comprtamiento del archiv
	//BTGhostController.cpp, pero con un compartamiento diferente.
	auto filter = std::make_shared<Filter>();
	filter->addCondition(std::make_shared<Powerpill>());
	filter->addAction(std::make_shared<Frightened>());
	root->addChild(filter);
	
	//crear un nuevo filtro para el comportamiento de scatter, con la condicion de timeout y la accion de scatter.
	//el filtro significa que el comportamiento de scatter se ejecutara cada cierto tiempo, dependiendo de la condicion de timeout.
	auto filter2 = std::make_shared<Filter>();
	filter2->addCondition(std::make_shared<TimeOut>());
	filter2->addAction(std::make_shared<Scatter>());
	root->addChild(filter2);

}

PinkyController::~PinkyController() {

}

Move
PinkyController::getMove(const GameState& game){
	return PASS;	

	
}

Status PinkyPerseguir::update(){
	//implementar el comportamiento de pinky, usando el arbol de comportamiento creado en el constructor.
	//el comportamiento de pinky es intentar alcanzar a pac moviéndose paralelo a él.
	auto character = Info::getInfo()->in_character;
	auto gs = Info::getInfo()->in_gamestate;


	move MsPacManMove = gs->getPacmanMove();
	Move minMove=PASS;
	std::vector<Move> moves;
	if(character->getDirection()==PASS) {
		moves=gs->getMaze().getPossibleMoves(character->getPos());
	} else {
		moves = gs->getMaze().getGhostLegalMoves(character->getPos(), character->getDirection());
	}

	for(auto move : moves){
		auto newPos = gs.getMaze().getNewPosition(character->getPos(), move);
		auto pacmanPos = gs.getPacmanPos();
		float distance = sqrt(pow(newPos.first - pacmanPos.first, 2) + pow(newPos.second - pacmanPos.second, 2));
		if(distance < min){
			min = distance;
			minMove = move;
		}
	}

	return BH_SUCCESS;
}