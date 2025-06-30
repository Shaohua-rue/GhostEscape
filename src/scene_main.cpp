#include "scene_main.h"

void SceneMain::init()
{
    world_size_ =  game.getScreenSize() * 3.0f;  //世界大小为三倍屏幕大小
    camera_position_ = glm::vec2(-100.0f);
}

void SceneMain::update(float deltaTime)
{
    camera_position_ += glm::vec2(10.0f, 10.0f) *  deltaTime * 10.0f;
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
    game.drawBoundary(start,end,5.0f,{1.0f,1.0f,1.0f,1.0f});
}