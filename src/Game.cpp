#include "Game.h"
#include "Api.h"
#include "Logger.h"

#include <rlImGui.h>
#include <raymath.h>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

int Game::windowWidth = 800;
int Game::windowHeight = 600;
Vector2 Game::mousePosition = { 0, 0 };

float scale = 1.0f;

Camera camera = {
    { 50.0f, 50.0f, 50.0f },
    { 0.0f, 10.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    45.0f,
    CAMERA_PERSPECTIVE
};

Game::Game()
{
    isRunning = false;
    isLetterbox = false;
    renderTexture = { 0 };

    assetStore = AssetStore();
    registry = entt::registry();
}

Game::~Game()
{

}

void Game::Init()
{
    SetTraceLogCallback(Logger::RaylibCallback);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, "Krii by Vinny Horgan");
    SetWindowMinSize(windowWidth / 2, windowHeight / 2);
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    InitAudioDevice();

    if (isLetterbox)
    {
        renderTexture = LoadRenderTexture(windowWidth, windowHeight);
        SetTextureFilter(renderTexture.texture, TEXTURE_FILTER_POINT);
    }

    rlImGuiSetup(true);

    isRunning = true;

    Api::Register(lua);

    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);

    sol::load_result result = lua.load_file("demo/main.lua");
    if (!result.valid())
    {
        sol::error err = result;
        Logger::Err(err.what());
    }
    else
    {
        lua.script_file("demo/main.lua");

        sol::table conf = lua.create_named_table("conf");

        sol::function confFunc = lua["krii"]["conf"];
        if (confFunc.valid())
        {
            confFunc(conf);
        }

        std::string title = conf["title"];
        Logger::Warn(title);

        sol::function initFunc = lua["krii"]["init"];
        if (initFunc.valid())
        {
            initFunc();
        }
    }
}

void Game::Update()
{
    if (WindowShouldClose())
    {
        isRunning = false;
    }

    float dt = GetFrameTime();

    if (isLetterbox)
    {
        scale = MIN((float)GetScreenWidth() / windowWidth, (float)GetScreenHeight() / windowHeight);

        Vector2 realMouse = GetMousePosition();
        mousePosition.x = (realMouse.x - (GetScreenWidth() - (windowWidth * scale)) * 0.5f) / scale;
        mousePosition.y = (realMouse.y - (GetScreenHeight() - (windowHeight * scale)) * 0.5f) / scale;
        mousePosition = Vector2Clamp(mousePosition, { 0, 0 }, { (float)windowWidth, (float)windowHeight });
    }
    else
    {
        UpdateCamera(&camera);

        mousePosition = GetMousePosition();
    }

    sol::function updateFunc = lua["krii"]["update"];
    if (updateFunc.valid())
    {
        updateFunc(dt);
    }
}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (isLetterbox)
    {
        BeginTextureMode(renderTexture);
        ClearBackground(BLACK);

        sol::function drawFunc = lua["krii"]["draw"];
        if (drawFunc.valid())
        {
            drawFunc();
        };

        EndTextureMode();

        DrawTexturePro(renderTexture.texture, { 0.0f, 0.0f, (float)renderTexture.texture.width, (float)-renderTexture.texture.height },
            { (GetScreenWidth() - ((float)windowWidth * scale)) * 0.5f, (GetScreenHeight() - ((float)windowHeight * scale)) * 0.5f, (float)windowWidth* scale, (float)windowHeight* scale },
            { 0, 0 }, 0.0f, WHITE);
    }
    else
    {
        BeginMode3D(camera);

        sol::function draw3dFunc = lua["krii"]["draw3d"];
        if (draw3dFunc.valid())
        {
            draw3dFunc();
        };

        EndMode3D();

        sol::function drawFunc = lua["krii"]["draw"];
        if (drawFunc.valid())
        {
            drawFunc();
        };
    }

    rlImGuiBegin();

    sol::function guiFunc = lua["krii"]["gui"];
    if (guiFunc.valid())
    {
        guiFunc();
    };

    ImGui::ShowDemoWindow();

    rlImGuiEnd();

    EndDrawing();
}

void Game::Shutdown()
{
    if (isLetterbox)
    {
        UnloadRenderTexture(renderTexture);
    }

    rlImGuiShutdown();

    CloseAudioDevice();
    CloseWindow();
}

void Game::Run()
{
    while (isRunning)
    {
        Update();
        Draw();
    }
}
