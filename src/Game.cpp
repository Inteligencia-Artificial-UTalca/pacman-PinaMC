/*
 * Game.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: VIDEOJUEGOS UTALCA
 * 
 * En este codigo se crean los personajes y se asigna los controladores a cada uno de ellos.
 * se ejecuta en bucle y en cada iteracion se actualiza el estado del juego.
 * 
 * Fantasma 0 usa fsmController
 * Fantasma 1 usa btGhostController 
 * Fantasma 2 usa simpleController
 * Fantasma 3 usa randomController
 * Pacman usa simplePacmanController
 */
#include <chrono>
#include <thread>
#include "Game.h"
#include <algorithm>
#include "KeyboardController.h"
#include "RandomController.h"
#include "SimpleController.h"
#include "SimplePacmanController.h"
#include "BTGhostController.h"
#include "FSMController.h"
#include "Ghost.h"
#include "BlinkyController.h"
#include "InkyController.h"
#include "PinkyController.h"
#include "SueController.h"
#include "PacmanController.h"

extern bool quick;
extern bool nogui;

Game::Game():currentMap(0),
filenames{"mazes/a.txt","mazes/b.txt","mazes/c.txt","mazes/d.txt"},
gameState(filenames[currentMap]),
gv(std::make_unique<GameView>(std::vector<std::string>{"images/maze-a.png","images/maze-b.png","images/maze-c.png","images/maze-d.png"})) {

	auto pacman=std::make_shared<MsPacMan>(gameState.getMaze().getPacmanStart());
	gameState.addPacMan(pacman);
	//pacmanControl=std::make_shared<KeyboardController>(pacman);
	pacmanControl=std::make_shared<SimplePacmanController>(pacman);
	// pacmanControl=std::make_shared<PacmanController>(pacman);

	std::vector<std::shared_ptr<Ghost>> ghosts;
	for(int i=0;i<4;i++){
		auto ghost=std::make_shared<Ghost>(gameState.getMaze().getGhostStart()[i]);
		ghosts.push_back(ghost);
	}
	gameState.addGhosts(ghosts);
	ghostsControl.push_back(std::make_shared<FSMController>(ghosts[0]));
	ghostsControl.push_back(std::make_shared<BTGhostController>(ghosts[1]));
	ghostsControl.push_back(std::make_shared<SimpleController>(ghosts[2]));
	ghostsControl.push_back(std::make_shared<RandomController>(ghosts[3]));
	//  ghostsControl.push_back(std::make_shared<BlinkyController>(ghosts[0]));
	//  ghostsControl.push_back(std::make_shared<InkyController>(ghosts[1]));
	//  ghostsControl.push_back(std::make_shared<PinkyController>(ghosts[2]));
	//  ghostsControl.push_back(std::make_shared<SueController>(ghosts[3]));
}

const int NOSCORELIMIT = 10000;
void Game::run(){
	int lastScore=gameState.getScore();
	int framesWithoutChange=0;
	while(true){
		if(!nogui)
			gv->draw(currentMap,gameState);
		gameState.updatePacman(pacmanControl->getMove(gameState));
		gameState.updateEaten();
		std::vector<Move> ghostMoves;
		std::transform(ghostsControl.begin(), ghostsControl.end(), std::back_inserter(ghostMoves), [this](const std::shared_ptr<Controller> &ghost) { return ghost->getMove(gameState);});
		gameState.updateGhosts(ghostMoves);
		gameState.updateEaten();
		if(gameState.won()){
			currentMap=(currentMap+1)%filenames.size();
			gameState.reset(filenames[currentMap]);
		}else if(gameState.lost()){
			if(!nogui){
				std::cout<<"Aborting because of no progress."<<std::endl;
				std::cout<<"Final score: "<<lastScore<<std::endl;
			}else{
				std::cout<<lastScore<<std::endl;
			}
			break;
		}
		if(lastScore==gameState.getScore()){
			framesWithoutChange++;
		}else{
			lastScore=gameState.getScore();
			framesWithoutChange=0;
		}
		if(framesWithoutChange==NOSCORELIMIT){
			
			if(!nogui){
				std::cout<<"Aborting because of no progress."<<std::endl;
				std::cout<<"Final score: "<<lastScore<<std::endl;
			}else{
				std::cout<<lastScore<<std::endl;
			}
			break;
		}
		if(!quick)
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}


}


