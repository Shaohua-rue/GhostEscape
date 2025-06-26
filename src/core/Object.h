#pragma once
#include "Game.h"
class Object {
public:
    Object() = default;
    virtual ~Object() = default;    //所有的类，不在构造函数和析构函数里面做任何事情

    virtual void init(){}   //需要初始化的事物，在init()函数里面做
    virtual void clean(){}  //需要清理的资源，在clean()函数里面做

    virtual void handleEvents(SDL_Event& event){}
    virtual void update(float deltaTime){}
    virtual void render(){}
protected:
    Game& game = Game::getInstance();
};