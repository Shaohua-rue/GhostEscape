#include "scene_main.h"

void SceneMain::init()
{
    world_size_ =  game.getScreenSize() * 3.0f;  //世界大小为三倍屏幕大小
}

void SceneMain::update(float deltaTime)
{
    //camera_position_ += glm::vec2(0.0f, 100.0f * deltaTime);
}

void SceneMain::render()
{
    renderBackground();
}

void SceneMain::handleEvents(SDL_Event& event)
{
}


void SceneMain::renderBackground()
{
    auto start = - camera_position_;
    auto end = world_size_ - camera_position_;
    game.drawGrid(start,end,80.0f,{0.5f,0.5f,0.5f,1.0f});
}