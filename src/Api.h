#pragma once

#include <sol/sol.hpp>

class Api
{
public:
    Api();
    ~Api();

    static void Register(sol::state& lua);
};
