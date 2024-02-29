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

    static sf::Texture* getTexture(const std::string& path);
    static const sf::Sprite & getBackground();
    static sf::Sound & getSoundMoveChip();
    static sf::Music & getSoundWin();
    static sf::Text& getText();


private:
    void addTexture(const std::string& path);
    void setFont(const std::string& pathFont);

    std::unordered_map<std::string, sf::Texture> textures;    

    sf::Sprite background;

    sf::Text text;
    sf::Font font;

    sf::Music soundWin;
    sf::Sound soundMoveChip;
    sf::SoundBuffer bufferMove;

    AssetManager() {}
    AssetManager(AssetManager const&) = delete;
    AssetManager& operator=(AssetManager const&) = delete;
};