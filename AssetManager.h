#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include "Color.h"

class AssetManager {
public:
    static AssetManager& instance() {
        static AssetManager staticAssetManager;
        return staticAssetManager;
    }

    static sf::Texture* getTexture(const std::string& path);
    static sf::Sprite & getBackground(const std::string& path);

    static sf::Music& getBackgroundMusic();
    static sf::Music& getSoundWin();
    static sf::SoundBuffer& getBuffer();

    static sf::Text& getText();
    static sf::Font& getFont();
    
   
    void setFont(const std::string& pathFont);
    void setBuffer(const std::string& pathFont);

private:
    void addTexture(const std::string& path);

    std::unordered_map<std::string, sf::Texture> textures;    

    sf::Sprite background;

    sf::Text text;
    sf::Font font;

    sf::Music backgroundMusic;
    sf::Music soundWin;


    sf::SoundBuffer buffer;

    AssetManager() {}
    AssetManager(AssetManager const&) = delete;
    AssetManager& operator=(AssetManager const&) = delete;
};