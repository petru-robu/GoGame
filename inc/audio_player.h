#ifndef AUDIO_PLAYER
#define AUDIO_PLAYER
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

#include "resource_manager.h"


class AudioPlayer 
{
private:
    std::vector<sf::Sound> activeSounds;
    
public:
    void playSound(const std::string& path);
    void update();
};


#endif