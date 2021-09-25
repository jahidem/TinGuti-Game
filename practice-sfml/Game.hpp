#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key, bool);

private:
    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingRight = false;
    bool mIsMovingLeft = false;

};