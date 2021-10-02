#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream> 
#include "Entity.h"
class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time);
    void render();
    void handlePlayerInput(sf::Event, bool);
    bool noneThere(int, int);
    bool CheckgameFinish();
    void afterGmProcessEvents();
    void afterGmUpdate(sf::Time);
    void afterGmRender();
    void mallReset();

private:
    //Guti Position
    const sf::Vector2f mInitial[10] = {
     sf::Vector2f(57.f,55.f),
     sf::Vector2f(360.f, 55.f),
     sf::Vector2f(660.f, 55.f),
     sf::Vector2f(50.f, 470.f),
     sf::Vector2f(360.f, 470.f),
     sf::Vector2f(660.f, 470.f),
     sf::Vector2f(75, 836)  ,
     sf::Vector2f(375, 836)  ,
     sf::Vector2f(655, 836)  ,
    sf::Vector2f(0.f,0.f)
    };
    const int mTo[9][9] = {
        {0,0,0,0,0,0,3,1,4},
        {1,1,1,1,1,1,4,0,2},
        {2,2,2,2,2,2,1,4,5},
        {3,3,3,3,3,3,0,4,6},
        {4,0,1,2,3,5,6,7,8},
        {5,5,5,5,5,5,2,4,8},
        {6,6,6,6,6,6,3,4,7},
        {7,7,7,7,7,7,6,4,8},
        {8,8,8,8,8,8,5,4,7}
    };
    const int finishState[8][3] = {
        {6,7,8},
        {2,5,8},
        {0,4,8},
        {2,4,6},
        {1,4,7},
        {3,4,5},
        {0,3,6},
        {0,1,2}
    };
    
    static int mWin[];
    static int preFirst;

    sf::RectangleShape mBlur;
    sf::RenderWindow mWindow;
    Entity allPlayer[7] ;
    int allPos[6];
    bool mMove[7], mPing=false,turn=1, gameRun=true;
    sf::Text mWinText,textOne, textOne1,textTwo;
    sf::Font fontWin,fontNorm;


    const int PlayerSpeed = 300;
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};