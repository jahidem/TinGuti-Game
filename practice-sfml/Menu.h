#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream> 
#include "Entity.h"
class Menu {
public:
    Menu();
    int run();
private:
    void processEvents();
    void update(sf::Time);
    void render();
    void handlePlayerInput(sf::Keyboard::Key, bool);

private:
    sf::RenderWindow mWindow;
    sf::Sprite mKagoj,mPlayerOne,
        mPlayerTwo;
    sf::Texture mTex,mTex1,mTex2;
    sf::Font fontTin;
    sf::Text textArr[3];

    int mPointing;
    const int PlayerSpeed = 300;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};