#include "../inc/audio_player.h"

AudioPlayer::AudioPlayer():
button_sound(*ResourceManager::getInstance().getSoundBuffer("./audio/button.wav")),
piece_sound(*ResourceManager::getInstance().getSoundBuffer("./audio/stone_place.wav")),
error_piece_sound(*ResourceManager::getInstance().getSoundBuffer("./audio/wrong.wav"))
{
    if(!music.openFromFile("./audio/music.ogg"))
    {
        std::cerr<<"Cannot open music file!\n";
    }
}

AudioPlayer& AudioPlayer::getInstance()
{
    static AudioPlayer instance;
    return instance;
}

void AudioPlayer::playButtonSound()
{
    button_sound.play();
}
void AudioPlayer::playPieceSound()
{
    piece_sound.play();
}
void AudioPlayer::playErrorPieceSound()
{
    error_piece_sound.play();
}
void AudioPlayer::playMusic()
{
    music.setVolume(40);
    music.setLooping(true);
    music.play();
}

void AudioPlayer::stopMusic()
{
    music.pause();
}