#include "AssetManager.h"


void AssetManager::addTexture(const std::string& path)
{
    auto& texture = textures[path];
    texture.loadFromFile(path);
}

sf::Texture* AssetManager::getTexture(const std::string &path)
{
    auto& manager = AssetManager::instance();
    auto textures = AssetManager::instance().textures;

    if (auto pair_found = manager.textures.find(path); pair_found != manager.textures.end())
        return &pair_found->second;

    manager.addTexture(path);

    return &manager.textures[path];
}

 sf::Sprite& AssetManager::getBackground()
{
    auto& manager = AssetManager::instance();
    auto texture = *manager.getTexture("img/background.jpg");

    manager.background.setColor(userColor::Aqua);
    manager.background.setTexture(texture);
    return manager.background;
}

sf::Sound& AssetManager::getSoundMoveChip()
{
    auto &manager = AssetManager::instance();
    manager.bufferMove.loadFromFile("music/move.ogg");
    manager.soundMoveChip.setBuffer(manager.bufferMove);

    return manager.soundMoveChip;
}

sf::Music& AssetManager::getSoundWin()
{
    auto &manager = AssetManager::instance();
    manager.soundWin.openFromFile("music/finish.ogg");

    return manager.soundWin;
}

void AssetManager::setFont(const std::string& pathFont) {
    font.loadFromFile(pathFont);
    text.setFont(font);
}


sf::Text& AssetManager::getText()
{
    auto &manager = AssetManager::instance();
    manager.setFont("arial.ttf");

    manager.text.setPosition(80, 200);
    manager.text.setCharacterSize(60);
    manager.text.setString("YOU WIN!!!");

    return manager.text;
}
