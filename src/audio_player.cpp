#include "../inc/audio_player.h"

void AudioPlayer::playSound(const std::string& path) 
{
    auto buffer = ResourceManager::getInstance().getSoundBuffer(path);

    sf::Sound sound(*buffer);
    sound.setVolume(100);
    sound.play();

    if (sound.getStatus() == sf::SoundSource::Status::Playing) {
        std::cout << "Sound is playing!\n";
    } else {
        std::cout << "Sound failed to play!\n";
    }
    
    activeSounds.push_back(std::move(sound));
}

void AudioPlayer::update() 
{
    for (auto it = activeSounds.begin(); it != activeSounds.end(); ) 
    {
        if (it->getStatus() == sf::SoundSource::Status::Stopped)
        {
            it = activeSounds.erase(it);
        }
        else 
        {
            it++;
        }      
    }
}