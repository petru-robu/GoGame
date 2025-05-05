#include "../inc/resource_manager.h"

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}

std::shared_ptr<sf::Font> ResourceManager::getFont(const std::string& path)
{
    if(fonts.find(path) != fonts.end())
        return fonts[path];
    
    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();

    if(!font->openFromFile(path))
    {
        std::cerr<<"Cannot open font!";
        return nullptr;
    }
    fonts[path] = font;
    return font;
}

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string& path)
{
    if(textures.find(path) != textures.end())
        return textures[path];
    
    std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();

    if(!texture->loadFromFile(path))
    {
        std::cerr<<"Cannot load texture!";
        return nullptr;
    }
    textures[path] = texture;
    return texture;

}

std::shared_ptr<sf::SoundBuffer> ResourceManager::getSoundBuffer(const std::string& path) 
{
    if (soundBuffers.find(path) != soundBuffers.end())
        return soundBuffers[path];

    auto buffer = std::make_shared<sf::SoundBuffer>();

    if (!buffer->loadFromFile(path))
    {
        std::cerr<<"Cannot load sounds!";
        return nullptr;
    }

    soundBuffers[path] = buffer;
    return buffer;
}