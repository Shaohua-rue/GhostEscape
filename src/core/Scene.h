#pragma once

#include "Object.h"
#include <vector>

class Scene : public Object {
public:
    Scene() = default;
    virtual ~Scene() = default;
    virtual void init() override{}
    virtual void update(float deltaTime) override{}
    virtual void render() override{}
    virtual void handleEvents(SDL_Event& event) override{}
    virtual void clean() override{}
private:
    glm::vec2 camera_position_ = glm::vec2(0.0f, 0.0f); //相机位置
    std::vector<Object*> objects_;  //场景中的物体
};