#pragma once

#include "AssetStore.h"

#define SOL_ALL_SAFETIES 1
#include <sol/sol.hpp>
#include <raylib.h>
#include <entt.hpp>

class Game
{
private:
    bool isRunning;
    bool isLetterbox;
    RenderTexture renderTexture;

    sol::state lua;
    AssetStore assetStore;
    entt::registry registry;

public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();
    void Shutdown();
    void Run();

    static int windowWidth;
    static int windowHeight;
    static Vector2 mousePosition;
};
