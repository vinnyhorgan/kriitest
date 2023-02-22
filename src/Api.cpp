#include "Api.h"
#include "Logger.h"

#include <raylib.h>

// Graphics
void rectangle(const std::string& mode, int x, int y, int width, int height)
{
    if (mode == "fill")
    {
        DrawRectangle(x, y, width, height, WHITE);
    }
    else if (mode == "line")
    {
        DrawRectangleLines(x, y, width, height, WHITE);
    }
}

void print(const std::string& message, int x, int y)
{
    DrawText(message.c_str(), x, y, 20, WHITE);
}

void circle(const std::string& mode, int x, int y, float radius)
{
    if (mode == "fill")
    {
        DrawCircle(x, y, radius, WHITE);
    }
    else if (mode == "line")
    {
        DrawCircleLines(x, y, radius, WHITE);
    }
}

void grid()
{
    DrawGrid(20, 10.0f);
}

Api::Api()
{

}

Api::~Api()
{

}

void Api::Register(sol::state& lua)
{
    sol::table krii = lua.create_named_table("krii");

    sol::table graphics = lua.create_named_table("graphics");
    krii.set("graphics", graphics);

    krii.set_function("log", [](const std::string& message) {
        Logger::Log(message);
    });

    krii.set_function("warn", [](const std::string& message) {
        Logger::Warn(message);
    });

    krii.set_function("err", [](const std::string& message) {
        Logger::Err(message);
    });

    graphics.set_function("rectangle", &rectangle);
    graphics.set_function("print", &print);
    graphics.set_function("circle", &circle);
    graphics.set_function("grid", &grid);
}
