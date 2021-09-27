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
    sf::Vector2f pos= sf::Vector2f();
    //Guti Position
    sf::Vector2f posOne1 = sf::Vector2f(-30.f,-46.f);
    sf::Vector2f posOne2 = sf::Vector2f(-283.f, -46.f);
    sf::Vector2f posOne3 = sf::Vector2f(-576.f, -46.f);

    sf::Vector2f posTwo1 = sf::Vector2f(-30.f, 346.f);
    sf::Vector2f posTwo2 = sf::Vector2f(283.f, 346.f);
    sf::Vector2f posTwo3 = sf::Vector2f(576.f, 346.f);

    sf::Vector2f posThree1 = sf::Vector2f(-30, 720);
    sf::Vector2f posThree2 = sf::Vector2f(283, 720);
    sf::Vector2f posThree3 = sf::Vector2f(576, 720);

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