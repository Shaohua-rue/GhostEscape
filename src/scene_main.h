#pragma once

#include "core/Scene.h"

class SceneMain : public Scene {
public:
    SceneMain() = default;
    ~SceneMain() = default;
    void init() override;
    void update(float deltaTime) override;
    void render() override;
    void handleEvents(SDL_Event& event) override;
private:
    void renderBackground();
private:
    glm::vec2 world_size_ = glm::vec2(0);    //世界大小
};