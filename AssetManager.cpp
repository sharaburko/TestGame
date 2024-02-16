#include "AssetManager.h"


void AssetManager::addTexture(const std::string& path)
{
    auto& texture = textures[path];
    texture.loadFromFile(path);
}

const sf::Texture* AssetManager::getTexture(const std::string &path)
{
    if (auto pair_found = textures.find(path); pair_found != textures.end())
        return &pair_found->second;

    addTexture(path);

    return &textures[path];
}

const sf::Sprite& AssetManager::getBackground()
{
    background.setTexture(*instance().getTexture("img/background.jpg"));
    return background;
}

sf::Sound& AssetManager::getSoundMoveChip()
{
    bufferMove.loadFromFile("music/move.ogg");
    soundMoveChip.setBuffer(bufferMove);

    return soundMoveChip;
}

sf::Music& AssetManager::getSoundWin()
{
    soundWin.openFromFile("music/finish.ogg");

    return soundWin;
}

void AssetManager::setFont(const std::string& pathFont) {
    font.loadFromFile(pathFont);
    text.setFont(font);
}


sf::Text& AssetManager::getText()
{
    setFont("arial.ttf");

    text.setPosition(80, 200);
    text.setCharacterSize(60);

    return text;
}
