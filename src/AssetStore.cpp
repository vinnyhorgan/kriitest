#include "AssetStore.h"
#include "Logger.h"

AssetStore::AssetStore()
{

}

AssetStore::~AssetStore()
{

}

void AssetStore::AddTexture(const std::string& name, const std::string& path)
{
    Texture texture = LoadTexture(path.c_str());

    if (texture.id == 0)
    {
        Logger::Err("Failed to load texture: " + path);
    }
    else
    {
        textures[name] = texture;
        Logger::Log("Loaded texture: " + path);
    }
}

Texture AssetStore::GetTexture(const std::string& name)
{
    return textures[name];
}

void AssetStore::ClearTextures()
{
    for (auto& texture : textures)
    {
        UnloadTexture(texture.second);
    }

    textures.clear();
}