#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class AssetManager {
public:
    static AssetManager& instance() {
        static AssetManager staticAssetManager;
        return staticAssetManager;
    }
    const sf::Texture* getTexture(const std::string& path);
    void addTexture(const std::string& path);
    const sf::Sprite & getBackground();
    sf::Sound & getSoundMoveChip();
    sf::Music & getSoundWin();
    sf::Text& getText();
public:
    //sf::Text text;
    sf::Font font;

    //sf::Music soundWin;
    sf::Sound soundMoveChip;
    sf::SoundBuffer bufferMove;

private:
    std::unordered_map<std::string, sf::Texture> texture;    

    sf::Sprite background;

    sf::Text text;
    //sf::Font font;

    sf::Music soundWin;
    //sf::Sound soundMoveChip;
    //sf::SoundBuffer bufferMove;

    AssetManager();
    AssetManager(AssetManager const&);
    AssetManager& operator=(AssetManager const&);
};