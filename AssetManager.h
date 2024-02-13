#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct AssetManager {
    sf::Texture textureChip;
    sf::Texture textureSquare;
    sf::Music soundWin;
    sf::Sound soundMoveChip;
    sf::Sprite background;
    sf::Text text;
    sf::Texture textureBackground;
    sf::Font font;
    sf::SoundBuffer bufferMove;

    static AssetManager& instance() {
        static AssetManager staticAssetManager;
        return staticAssetManager;
    }
private:
    AssetManager();
    AssetManager(AssetManager const&);
    AssetManager& operator=(AssetManager const&);

};