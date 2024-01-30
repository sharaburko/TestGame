#include "AssetManager.hpp"

AssetManager::AssetManager() {
    font.loadFromFile("arial.ttf");
    textureChip.loadFromFile("img/chip.png");
    textureSquare.loadFromFile("img/point.png");
    textureBackground.loadFromFile("img/background.jpg");
    background.setTexture(textureBackground);
    bufferMove.loadFromFile("music/move.ogg");
    soundMoveChip.setBuffer(bufferMove);
    soundWin.openFromFile("music/finish.ogg");
    text.setFont(font);
    text.setPosition(80, 200);
    text.setCharacterSize(60);
}
