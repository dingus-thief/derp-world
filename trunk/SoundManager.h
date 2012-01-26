#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include <SFML/Audio.hpp>
#include <map>

class SoundManager
{
    public:
        SoundManager();
        void play(const std::string& name);

    private:
        std::map<std::string, sf::SoundBuffer*> sounds;

};

#endif // SOUNDMANAGER_H
