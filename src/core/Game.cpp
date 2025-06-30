#include "Game.h"
#include "../scene_main.h"
/**
 * @brief 初始化相关资源
*/
void Game::init(std::string title, int width, int height)
{
    screen_size_ = glm::vec2(width, height);
    // SDL3初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL初始化失败: %s\n", SDL_GetError());
    }
    // 不需要进行SDL_image初始化
    // SDL3_Mixer初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer初始化失败: %s\n", SDL_GetError());
    }
    if (!Mix_OpenAudio(0, NULL)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Mixer打开音频失败: %s\n", SDL_GetError());
    }
    Mix_AllocateChannels(16); // 分配16个音频通道
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4); // 设置音效音量

    // SDL3_TTF初始化
    if (!TTF_Init()){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_TTF初始化失败: %s\n", SDL_GetError());
    }
    // 创建窗口与渲染器
    SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "创建窗口或渲染器失败: %s\n", SDL_GetError());
    }
    // 设置窗口逻辑分辨率
    SDL_SetRenderLogicalPresentation(renderer_, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    //  计算帧间隔时间
    frameDelta_ = 1e9 / fps_;
    deltaTime_ = frameDelta_ / 1.0e9;

    //创建场景
    current_scene_ = new SceneMain();
    current_scene_->init();
}
void Game::run()
{
    while (isRunning_)
    {
        auto startTime = SDL_GetTicksNS();
        handleEvents();
        update(deltaTime_);
        render();
        auto endTime = SDL_GetTicksNS();

        auto elapsedTime = endTime - startTime;

        if(elapsedTime < frameDelta_)
        {
            SDL_DelayNS(frameDelta_ - elapsedTime);
            deltaTime_ = frameDelta_ / 1.0e9;
        }else{
            deltaTime_ = elapsedTime / 1.0e9;
        }
    }

}
void Game::clean()
{
    //删除场景
    if(current_scene_ != nullptr){
        current_scene_->clean();
        delete current_scene_;
    }
    //释放渲染器和窗口
    if(renderer_ != nullptr){
        SDL_DestroyRenderer(renderer_);
    }
    if(window_ != nullptr){
        SDL_DestroyWindow(window_);
    }
    //退出Mix
    Mix_CloseAudio();
    Mix_Quit();

    //退出TTF
    TTF_Quit();

    //退出SDL
    SDL_Quit();
}

void Game::handleEvents()
{ 
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                isRunning_ = false;
                break;
            default:
                current_scene_->handleEvents(event);
                break;
        }
    }
}

void Game::update(float deltaTime)
{
    current_scene_->update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    current_scene_->render();
    SDL_RenderPresent(renderer_);
}

/****
 * @brief 绘制网格
 * ****/
void Game::drawGrid(const glm::vec2& top_left, const glm::vec2& bottom_right,float grid_width, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);

    for(float x = top_left.x; x < bottom_right.x; x += grid_width){
        SDL_RenderLine(renderer_, x, top_left.y, x, bottom_right.y);
    }

    for(float y = top_left.y; y < bottom_right.y; y += grid_width){
        SDL_RenderLine(renderer_, top_left.x, y, bottom_right.x, y);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

/******
 * @brief 绘制边界
 * *****/
void Game::drawBoundary(const glm::vec2& top_left, const glm::vec2& bottom_right, float boundary_width, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    for(float i = 0; i < boundary_width; i++){
        SDL_FRect rect = {
        top_left.x - i,
        top_left.y - i,
        bottom_right.x - top_left.x + i * 2,
        bottom_right.y - top_left.y + i * 2
        };
        SDL_RenderRect(renderer_, &rect);
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1);
}

