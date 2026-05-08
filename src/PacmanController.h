#pragma once

#include "Controller.h"

//controles de pacman, por ahora no hace nada, pero se puede extender para usar el teclado o lo que quieran
class PacmanController: public Controller {

public:
	PacmanController(std::shared_ptr<Character> character);
	virtual ~PacmanController();
	virtual Move getMove(const GameState& game)override;
};

