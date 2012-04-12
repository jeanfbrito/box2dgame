#include "ResourceManager.h"
#include <iostream>

sfge::ResourceManager* sfge::ResourceManager::mgr = 0;

namespace sfge
{
    ResourceManager::ResourceManager() : textureDir("")
    {
        //ctor
    }

    ResourceManager::~ResourceManager()
    {
        //dtor
    }

    ResourceManager* ResourceManager::instance()
    {
        if(mgr == NULL)
            mgr = new ResourceManager;

        return mgr;
    }

    sf::Texture& ResourceManager::getTexture(const std::string& name)
    {
        if(textures.find(name) != textures.end())
            return(*textures[name]);
        else
        {
            sf::Texture* texture = new sf::Texture;

            if(!texture->loadFromFile(textureDir + name))
                std::cout<<"Could not load image "<<textureDir+name;
            else
            {
                textures[name] = texture;
            }
            return *texture;
        }
    }

    sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name)
    {
        if(soundBuffers.find(name) != soundBuffers.end())
            return(*soundBuffers[name]);
        else
        {
            sf::SoundBuffer* sound = new sf::SoundBuffer;

            if(!sound->loadFromFile(audioDir + name))
                std::cout<<"Could not load audio file "<<audioDir+name;
            else
                soundBuffers[name] = sound;
            return *sound;
        }
    }

    void ResourceManager::playSound(const std::string& name)
    {
        if(sounds.size() < 5)
        {
            if(soundBuffers.find(name) != soundBuffers.end())
            {
                sf::Sound* sound = new sf::Sound(*soundBuffers[name]);
                sound->play();
                sounds.push_back(sound);
            }
            else
            {
                sf::SoundBuffer* tmp = new sf::SoundBuffer;
                tmp->loadFromFile("Data/Audio/" + name);
                soundBuffers[name] = tmp;
                sf::Sound* sound = new sf::Sound(*soundBuffers[name]);
                sound->play();
                sounds.push_back(sound);
            }
        }
    }

    void ResourceManager::releaseStoppedSounds()
    {
        for(auto itr = sounds.begin(); itr != sounds.end(); itr++)
        {
            if((*itr)->getStatus() == sf::Sound::Status::Stopped)
            {
                delete (*itr);
                itr = sounds.erase(itr);
            }
        }
    }

    void ResourceManager::setTextureDir(const std::string& dir)
    {
        textureDir = dir;
    }

    void ResourceManager::setAudioDir(const std::string& dir)
    {
        audioDir = dir;
    }
}
