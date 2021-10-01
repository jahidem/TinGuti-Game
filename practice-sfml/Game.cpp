#include "Game.h"

Game::Game()
    :mWindow(sf::VideoMode(800, 950), "It's TinGuti", sf::Style::Close)
     {
    for (int u = 0; u < 6; u++) mMove[u] = false;
    allPlayer[6].load("asset/board2.jpg", sf::Vector2f(800, 950),6);
    for(int u=0;u<3;u++) allPlayer[u].load("asset/play1.png", sf::Vector2f(70, 70),u);
    for(int u=3;u<6;u++) allPlayer[u].load("asset/play2.png", sf::Vector2f(70, 70),u+3);

    for(int u=0;u<3;u++) allPlayer[u].setPosition(mInitial[u]);
    for (int u = 3; u < 6; u++) allPlayer[u].setPosition(mInitial[u+3]);
    allPlayer[6].setPosition(mInitial[9]);

    sf::Vector2f pos =allPlayer[0].getPosition(); std::cout << pos.x << " " << pos.y << "\n";
}

void Game::run() {
    
   sf::Music music;
   if (!music.openFromFile("asset/Aoi_Shiori.ogg"))
   {
       std::cout << "error";
   } 
   //music.setPitch(2);           // increase the pitch
   music.setVolume(10);         // reduce the volume
   music.setLoop(true);
    //music.play();
   

    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        mWindow.setMouseCursor(cursor);

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
}


void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
       switch (event.type){
         case sf::Event::Closed:
                mWindow.close();
        case sf::Event::MouseButtonPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::MouseButtonReleased:
            handlePlayerInput(event.key.code, false);
            break;
            
        }
    }
}
void Game::update(sf::Time deltaTime) {
    if (mPing) {

        for (int u = 0; u < 6; u++) {
            int f = 1;
            sf::Vector2f pos = allPlayer[u].getPosition();
            for (int u = 0; u < 9; u++) {
                if (mInitial[u] == pos) f = 0;
            }
            if (f) {
                std::vector<std::pair<int, int>> disFromPos;
                for (int v = 0; v < 8; v++) {
                    int dis = int(abs(mInitial[mTo[allPlayer[u].mPos][v]].x - allPlayer[u].getPosition().x) +
                        abs(mInitial[mTo[allPlayer[u].mPos][v]].y - allPlayer[u].getPosition().y));
                    disFromPos.push_back({ dis,mTo[allPlayer[u].mPos][v] });

                }sort(disFromPos.begin(), disFromPos.end());
                for (auto x : disFromPos) {
                    if (noneThere(x.second, allPlayer[u].mPos)) {
                        allPlayer[u].setPosition(mInitial[x.second]), mPing = false;
                            if (allPlayer[u].mPos != x.second) turn = 1 - turn;
                            allPlayer[u].mPos = x.second;
                            break;
                    }
                }
            }
        }

     }
    else {
        int u = 0;
        if (!turn) u = 3;
        for (int a = u; a < u + 3; a++)
            if (mMove[a])
                allPlayer[a].setPosition(
                    static_cast<sf::Vector2f>
                    (sf::Mouse::getPosition(mWindow)) - sf::Vector2f(50.f, 50.f));
    }
    

}
void Game::render() {
    sf::Color color = sf::Color(123, 123, 142,255);
    mWindow.clear(color);
    for (int u = 6; u >= 0; u--) {
        mWindow.draw(allPlayer[u]);
    }
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    sf::Vector2i pos = sf::Mouse::getPosition(mWindow); std::cout << pos.x << " " << pos.y << "\n";
    if (key == sf::Mouse::Left){
        if (isPressed) {
            sf::Cursor cursor;
            if (cursor.loadFromSystem(sf::Cursor::Hand))
                mWindow.setMouseCursor(cursor);
            for (int u = 0; u < 6; u++) {
                int Px =(int) allPlayer[u].getPosition().x,
                    Py =(int) allPlayer[u].getPosition().y;
                if (Px < pos.x && pos.x < Px + 70 && Py < pos.y && pos.y < Py + 70)
                    mMove[u] = true,mPing=false;
            }
        }
        else {
            for (int u = 0; u < 6; u++) mMove[u] = false, mPing = true;
            sf::Cursor cursor;
            if (cursor.loadFromSystem(sf::Cursor::Arrow))
                mWindow.setMouseCursor(cursor);
        }
        }
   

}

bool Game::noneThere(int toGo, int meNow) {
    if (toGo != meNow) {
        for (int u = 0; u < 6; u++) 
            if(allPlayer[u].mPos == toGo)
        return false;
    }
    return true;
}

