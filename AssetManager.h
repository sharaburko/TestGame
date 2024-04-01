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
    static sf::Sound & getSoundMoveChip();
    static sf::Sound& getSoundSelectItemMenu();
    static sf::Music & getSoundWin();
    static sf::Music& getBackgroundMusic();
    static sf::Texture & getImgCursor();

    static sf::Text& getText();
    void setText(const std::string text, const sf::Color & color = sf::Color::White, const std::string pathText = "arial.ttf");
    static sf::Font& getFont();
    void setFont(const std::string& pathFont);
    void setImgCursor(std::string pathCursor);

private:
    void addTexture(const std::string& path);

    std::unordered_map<std::string, sf::Texture> textures;    

    sf::Sprite background;

    sf::Text text;
    sf::Font font;

    sf::Texture imgCursor;

    sf::Music backgroundMusic;
    sf::Music soundWin;
    sf::Sound soundMoveChip;
    sf::Sound soundSelectItemMenu;
    sf::SoundBuffer buffer;

    const sf::Cursor getCursor();

    AssetManager() {}
    AssetManager(AssetManager const&) = delete;
    AssetManager& operator=(AssetManager const&) = delete;
};