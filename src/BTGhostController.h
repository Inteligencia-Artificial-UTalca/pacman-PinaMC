/*
 * BTGhostController.h
 *
 *  Created on: May 2, 2018
 *      Author: VIDEOJUEGOS UTALCA
 */

#ifndef BTGHOSTCONTROLLER_H_
#define BTGHOSTCONTROLLER_H_

#include "Controller.h"
#include "BehaviorTree.h"
#include <chrono>

#include <random>
class Info{
    static Info *info;
    Info(){}

public:
    static Info* getInfo(){
        if(info==nullptr)info = new Info();
        return info;
    }
    const GameState* in_gamestate;
    Move out_move;
    std::shared_ptr<Character> in_character;
};

class BTGhostController: public Controller {
private:
    std::shared_ptr<Composite> root;
public:
	BTGhostController(std::shared_ptr<Character> character);
	virtual ~BTGhostController();
	virtual Move getMove(const GameState& gs) override;
};

class Chase : public Behavior{
public:
    virtual Status update() override;

};

class Frightened : public Behavior{
private:
    std::mt19937 e;
    std::uniform_int_distribution<int> uniform_dist;
public:
    virtual Status update() override;
    Frightened ();

};

class Scatter : public Behavior{
private:
    std::pair<int,int> target;

public:
    virtual Status update() override;
    Scatter();

};

class Powerpill : public Behavior{
public:
    virtual Status update() override;
};

class TimeOut : public Behavior{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
public:
    virtual Status update() override;
    TimeOut ();
};

#endif /* BTGHOSTCONTROLLER_H_ */