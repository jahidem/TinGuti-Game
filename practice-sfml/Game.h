#pragma once
#include <SFML/Graphics.hpp>
#include"TextureHolder.h"
#include"enums.h"
#include<iostream>
class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time);
    void render();
    void handlePlayerInput(sf::Keyboard::Key, bool);

private:
    sf::RenderWindow mWindow;
    TextureHolder textures;
    sf::Sprite gameBoard,mPlayerOne,mPlayerTwo;
    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingRight = false;
    bool mIsMovingLeft = false;
    const int PlayerSpeed = 400;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};