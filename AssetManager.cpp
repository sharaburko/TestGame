#include "AssetManager.h"


void AssetManager::addTexture(const std::string& path)
{
    sf::Texture tempTexture;
    tempTexture.loadFromFile(path);
    texture.emplace(path, tempTexture);
}

const sf::Texture* AssetManager::getTexture(const std::string &path)
{
    addTexture(path);
    return &texture[path];
}

const sf::Sprite& AssetManager::getBackground()
{
    background.setTexture(*instance().getTexture("img/background.jpg"));
    return background;
}

sf::Sound& AssetManager::getSoundMoveChip()
{
    return soundMoveChip;
}

sf::Music& AssetManager::getSoundWin()
{
    return soundWin;
}

sf::Text& AssetManager::getText()
{
    return text;
}

AssetManager::AssetManager() {
    font.loadFromFile("arial.ttf");
    bufferMove.loadFromFile("music/move.ogg");
    soundMoveChip.setBuffer(bufferMove);
    soundWin.openFromFile("music/finish.ogg");
    text.setFont(font);
    text.setPosition(80, 200);
    text.setCharacterSize(60);
}
