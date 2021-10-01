#include "Menu.h"
Menu::Menu(): mPointing(0),
    mWindow(sf::VideoMode(550,450), "Main Menu", sf::Style::None) {
    mTex.loadFromFile("asset/lava.jpg", sf::IntRect(100, 0, 550, 450));
    mTex1.loadFromFile("asset/play1.png");
    mTex2.loadFromFile("asset/play2.png");
    
    mPlayerOne.setTexture(mTex1);
    mPlayerTwo.setTexture(mTex2);
    mKagoj.setTexture(mTex);
    
    mKagoj.setPosition(0.f, 0.f);
    mPlayerOne.setPosition(40.f, 50.f);
    mPlayerTwo.setPosition(430.f, 50.f);

    if (!fontTin.loadFromFile("asset/karma.ttf")) std::cout << "Couldn't load";
    sf::Color color = sf::Color(255, 255, 255, 210);
    for (int u = 0; u < 3; u++) {
        textArr[u].setFont(fontTin);
        textArr[u].setFillColor(color);
        textArr[u].setCharacterSize(45);
    }
    textArr[0].setString("Start Tin_Guti");
    textArr[2].setString("Exit");
    textArr[1].setString("Learn How to play");

    textArr[0].setPosition(100.f, 100.f);
    textArr[2].setPosition(200.f, 300.f);
    textArr[1].setPosition(80.f, 200.f);

}

int Menu::run() {
    mPointing=0;
    sf::Music music;
    if (!music.openFromFile("asset/Scary_wav.ogg"))
    {
        std::cout << "error";
    }
    //music.setPitch(2);           // increase the pitch
    music.setVolume(10);         // reduce the volume
    music.setLoop(true);
    music.play();

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
        render();
    }
    return mPointing;
}

void Menu::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, false);
            break;
           
        }
    }
}

void Menu::update(sf::Time)
{
    for (int u = 0; u < 3; u++) {
        if (u == mPointing)
            textArr[u].setFillColor(sf::Color::Cyan);
        else
            textArr[u].setFillColor(sf::Color::White);
    }
}

void Menu::render()
{
    mWindow.clear();
    mWindow.draw(mKagoj);
    mWindow.draw(mPlayerOne);
    mWindow.draw(mPlayerTwo);
    for(int u=0;u<3;u++)
        mWindow.draw(textArr[u]);

    mWindow.display();
}

void Menu::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Down)
        mPointing++, mPointing %= 3;
    else if (key == sf::Keyboard::Up)
        mPointing--,
        mPointing += 3,
        mPointing %= 3;
    else if (key == sf::Keyboard::Enter)
        mWindow.close();
    else if (key == sf::Keyboard::Escape)
        mPointing = 2, mWindow.close();

}
