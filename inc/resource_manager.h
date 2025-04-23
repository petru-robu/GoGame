#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>


class ResourceManager
{
private:
    std::map<std::string, std::shared_ptr<sf::Font>> fonts;
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;

    ResourceManager() {}
    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;

    
public:
    static ResourceManager& getInstance();
    std::shared_ptr<sf::Font> getFont(const std::string& path);
    std::shared_ptr<sf::Texture> getTexture(const std::string& path);

};



#endif