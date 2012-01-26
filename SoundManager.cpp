#include "SoundManager.h"

SoundManager::SoundManager()
{

}


void SoundManager::play(const std::string& name)
{
    if(sounds.find(name) != sounds.end())
    {
        sf::Sound* sound = new sf::Sound(*sounds[name]);
        sound->Play();
    }
    else
    {
        sf::SoundBuffer* tmp = new sf::SoundBuffer;
        tmp->LoadFromFile("Data/Audio/" + name);
        sounds[name] = tmp;
        sf::Sound* sound = new sf::Sound(*sounds[name]);
        sound->Play();
    }

}
