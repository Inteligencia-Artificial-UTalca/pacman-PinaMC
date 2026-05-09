#pragma once

#include "Controller.h"
#include "BehaviorTree.h"
#include "BTGhostController.h"
#include <memory>
#include <chrono>

//puse : public behavior para poder usarlo como una accion dentro del arbol de comportamiento, 
//pero tambien hereda de controller para poder ser usado como controlador de un fantasma.
class PinkyController: public Behavior {

	public:
	virtual status update() override;
	private:
};

//hereda de controller para ser usado como controlador de un fantasma 
class PinkyController : public Controller {
public:
	PinkyController(std::shared_ptr<Character> character);
	virtual ~PinkyController();
	virtual Move getMove(const GameState& game) override;

private :
	std::shared_ptr<Composite> root;
};