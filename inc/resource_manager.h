#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "game_exceptions.h"


class ResourceManager
{
private:
    std::map<std::string, std::shared_ptr<sf::Font>> fonts;
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;

    ResourceManager() {}
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;

    
public:
    static ResourceManager& getInstance();
    std::shared_ptr<sf::Font> getFont(const std::string& path);
    std::shared_ptr<sf::Texture> getTexture(const std::string& path);
    std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string& path);

};



#endif