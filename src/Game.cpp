#include "Game.h"

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
}
void Game::run()
{
    while (isRunning_)
    {
        auto startTime = SDL_GetTicksNS();
        handleEvents();
        update(12.0f);
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
        SDL_Log("FPS: %f",1.0/deltaTime_);
    }

}
void Game::clean()
{

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
                break;
        }
    }
}

void Game::update(float deltaTime)
{
}

void Game::render()
{
    
}


