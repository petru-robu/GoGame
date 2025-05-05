#ifndef AUDIO_PLAYER
#define AUDIO_PLAYER
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

#include "resource_manager.h"


class AudioPlayer 
{
private:
    sf::Sound button_sound;
    sf::Sound piece_sound;
    sf::Sound error_piece_sound;

    sf::Music music;

    AudioPlayer();
    AudioPlayer(const AudioPlayer&) = delete;
    void operator=(const AudioPlayer&) = delete;
    
public:

    static AudioPlayer& getInstance();

    void playButtonSound();
    void playPieceSound();
    void playErrorPieceSound();
    void playMusic();
};


#endif