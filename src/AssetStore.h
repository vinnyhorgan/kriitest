#pragma once

#include <map>
#include <string>
#include <raylib.h>

class AssetStore
{
private:
    std::map<std::string, Texture> textures;

public:
    AssetStore();
    ~AssetStore();

    void AddTexture(const std::string& name, const std::string& path);
    Texture GetTexture(const std::string& name);
    void ClearTextures();
};
