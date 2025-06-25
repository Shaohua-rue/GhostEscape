#pragma once
#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <glm/glm.hpp>

class Game
{
public:
    static Game& getInstance()
    {
        static Game instance;
        return instance;
    }

    void init(std::string title, int width, int height);
    void run();
    void handleEvents();
    void update(float deltaTime);
    void render();
    void clean();

    
private:
    Game() = default;
    ~Game()
    {
        clean();
    }
    Game(const Game& game) = delete;
    Game& operator= (const Game& game) = delete;
private:
    bool isRunning = true;

    glm::vec2 screen_size_ = glm::vec2(0); // 屏幕大小
    bool is_running_ = true; // 游戏是否运行

    SDL_Window* window_ = nullptr; // 窗口
    SDL_Renderer* renderer_ = nullptr; // 渲染器
};