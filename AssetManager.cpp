#include "AssetManager.h"


void AssetManager::addTexture(const std::string& path)
{
    auto& texture = textures[path];
    texture.loadFromFile(path);
}


sf::Texture* AssetManager::getTexture(const std::string &path)
{
    auto& manager = AssetManager::instance();

    if (auto pair_found = manager.textures.find(path); pair_found != manager.textures.end())
        return &pair_found->second;

    manager.addTexture(path);

    return &manager.textures[path];
}

 sf::Sprite& AssetManager::getBackground(const std::string& path)
{
    auto& manager = AssetManager::instance();
    auto& sprite = AssetManager::instance().background;
    auto& texture = *manager.getTexture(path);

    //manager.background.setColor(userColor::Aqua);
    sprite.setTexture(texture);

    return sprite;
}

sf::Sound& AssetManager::getSoundMoveChip()
{
    auto &manager = AssetManager::instance();
    manager.buffer.loadFromFile("music/move.ogg");
    manager.soundMoveChip.setBuffer(manager.buffer);

    return manager.soundMoveChip;
}

sf::Sound& AssetManager::getSoundSelectItemMenu()
{
    auto& manager = AssetManager::instance();
    manager.buffer.loadFromFile("music/click.mp3");
    manager.soundSelectItemMenu.setBuffer(manager.buffer);

    return manager.soundSelectItemMenu;
}

sf::Music& AssetManager::getSoundWin()
{
    auto &manager = AssetManager::instance();
    manager.soundWin.openFromFile("music/finish.ogg");

    return manager.soundWin;
}

sf::Music& AssetManager::getBackgroundMusic()
{
    auto& manager = AssetManager::instance();
    manager.backgroundMusic.openFromFile("music/music.mp3");
    manager.backgroundMusic.setLoop(true);

    return manager.backgroundMusic;
}

sf::Texture& AssetManager::getImgCursor() {
    auto &manager = AssetManager::instance();
    manager.setImgCursor("img/cursor.png");
    return manager.imgCursor;
}

void AssetManager::setFont(const std::string& pathFont) {
    font.loadFromFile(pathFont);    
}

void AssetManager::setImgCursor(std::string pathCursor) {
    imgCursor.loadFromFile(pathCursor);
}

void AssetManager::setText(const std::string text, const sf::Color& color, const std::string pathText) {
    auto& manager = AssetManager::instance();

    manager.setFont(pathText);
    manager.text.setFont(manager.font);
    manager.text.setPosition(80, 200);
    manager.text.setCharacterSize(60);
    manager.text.setString(text);
    manager.text.setFillColor(color);
}

sf::Text& AssetManager::getText() {
    auto& manager = AssetManager::instance();
    return manager.text;
}

sf::Font& AssetManager::getFont()
{
    auto& manager = AssetManager::instance();
    return manager.font;
}
