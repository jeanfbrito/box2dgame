#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <list>

#define rm sfge::ResourceManager::instance()

namespace sfge
{
    class ResourceManager
    {
        public:
            ~ResourceManager();

            static ResourceManager* instance();

            void releaseStoppedSounds();

            sf::Texture& getTexture(const std::string& name);
            sf::SoundBuffer& getSoundBuffer(const std::string& name);
            void playSound(const std::string& name);
            void setTextureDir(const std::string& dir);
            void setAudioDir(const std::string& dir);

        protected:
            ResourceManager();

        private:
            static ResourceManager* mgr;
            std::string textureDir;
            std::string audioDir;
            std::map<std::string, sf::Texture*> textures;
            std::map<std::string, sf::SoundBuffer*> soundBuffers;
            std::list<sf::Sound*> sounds;
    };
}
#endif // RESOURCEMANAGER_H
