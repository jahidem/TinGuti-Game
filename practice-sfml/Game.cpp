#include "Game.h"

Game::Game()
    :mWindow(sf::VideoMode(800, 950), "It's TinGuti")
    {
    textures.load(textureId::IdLandscape, "asset/board2.jpg");
    textures.load(textureId::IdPlayerOne, "asset/playerone5.png");
    textures.load(textureId::IdPlayerTwo, "asset/playetwo2.png");

    gameBoard.setTexture(textures.get(textureId::IdLandscape));
    gameBoard.setPosition(0.f,0.f);

    mPlayerOne.setTexture(textures.get(textureId::IdPlayerOne));
    mPlayerOne.setPosition(posThree1);

    mPlayerTwo.setTexture(textures.get(textureId::IdPlayerTwo));
    mPlayerTwo.setPosition(290.f, 340.f);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        const  sf::Vector2f hi = mPlayerOne.getPosition();
        if (pos.x != hi.x || pos.y != hi.y) 
            std::cout << pos.x << " " << pos.y<<"\n", pos.x = hi.x, pos.y = hi.y;
         render();
    }
}


void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}
void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingRight)
        movement.x += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    mPlayerOne.move(movement * deltaTime.asSeconds());

}
void Game::render() {
    sf::Color color = sf::Color(123, 123, 142,255);
    mWindow.clear(color);
    mWindow.draw(gameBoard);
    mWindow.draw(mPlayerOne);
    mWindow.draw(mPlayerTwo);
    
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;

}


