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

    if(!fontWin.loadFromFile("asset/karma.ttf")) std::cout<<"Couldn't load";
    if (!fontNorm.loadFromFile("asset/righteous.ttf")) std::cout << "Couldn't load";
    
    mWinText.setFont(fontWin);
    mWinText.setString("Win!!");
    mWinText.setCharacterSize(70);
    mWinText.setFillColor(sf::Color::Cyan);
    //mWinText.setStyle(sf::Text:: );
    mWinText.setPosition(240.f, 385.f);

    textOne.setFont(fontNorm);
    textOne.setCharacterSize(20);
    textOne.setFillColor(sf::Color::White);

    textTwo.setFont(fontNorm);
    textTwo.setCharacterSize(20);
    textTwo.setFillColor(sf::Color::White);

    textOne.setPosition(350.f,20.f);
    textTwo.setPosition(350.f,920.f);

    textOne1.setFont(fontNorm);
    textOne1.setCharacterSize(20);
    textOne1.setFillColor(sf::Color::White);

    sf::Color color(123, 123, 123, 15);
    mBlur.setSize(sf::Vector2f(400.f,150.f));
    mBlur.setFillColor(color);
    mBlur.setPosition(200.f, 370.f);
}

void Game::run() {
    
   sf::Music music;
   if (!music.openFromFile("asset/Scary_wav.ogg"))
   {
       std::cout << "error";
   } 
   //music.setPitch(2);           // increase the pitch
   music.setVolume(10);         // reduce the volume
   music.setLoop(true);
    music.play();
   

    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        mWindow.setMouseCursor(cursor);

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        if (gameRun) {
            processEvents();
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > TimePerFrame) {
                timeSinceLastUpdate -= TimePerFrame;
                processEvents();
                update(TimePerFrame);
            }

            if(!CheckgameFinish()) update(TimePerFrame),render();
            render();
        }
        else {
            afterGmProcessEvents();
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > TimePerFrame) {
                timeSinceLastUpdate -= TimePerFrame;
                afterGmProcessEvents();
                afterGmUpdate(TimePerFrame);
            }
            afterGmRender();
        }
    }
}


void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
       switch (event.type){
         case sf::Event::Closed:
                mWindow.close();
                break;
        case sf::Event::MouseButtonPressed:
            handlePlayerInput(event, true);
            break;
        case sf::Event::MouseButtonReleased:
            handlePlayerInput(event, false);
            break;
            
        }
        if (event.key.code == sf::Keyboard::Escape) {
           // mWindow.close();

    }
    }
}
void Game::update(sf::Time deltaTime) {
    std::string str = "Score: ";
    str += std::to_string(mWin[0]);
    textOne.setString(str);
  
    str = "Score: ";
    str += std::to_string(mWin[1]);
    textTwo.setString(str);
    

    if (mPing) {

        for (int u = 0; u < 6; u++) {
            int f = 1;
            sf::Vector2f pos = allPlayer[u].getPosition();
            for (int u = 0; u < 9; u++) {
                if (mInitial[u] == pos) f = 0;
            }
            if (f) {
                std::vector<std::pair<int, int>> disFromPos;
                for (int v = 0; v < 9; v++) {
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
        sf::Color color = sf::Color(123, 123, 142, 255);
        mWindow.clear(color);
        for (int u = 6; u >= 0; u--) {
            mWindow.draw(allPlayer[u]);
        }
        mWindow.draw(textOne);
        mWindow.draw(textTwo);
    mWindow.display();
}

void Game::afterGmRender() {
    mWindow.draw(mBlur);
    if (!turn)
        mWindow.draw(allPlayer[0]);
    else
        mWindow.draw(allPlayer[3]);
    mWindow.draw(mWinText);
    mWindow.draw(textOne1);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Event event, bool isPressed) {
    sf::Vector2i pos = sf::Mouse::getPosition(mWindow); 
    if (event.key.code == sf::Mouse::Left){
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


bool Game::CheckgameFinish() {
    bool runIt = true;
    int poss[3];
    for (int u = 0; u < 3; u++) {
        poss[u] = allPlayer[u].mPos;
    }
    std::sort(poss, poss + 3);
    int f;
    for (int u = 0; u < 7; u++) {
        f = 1;
        for (int v = 0; v < 3; v++) {
            if (finishState[u][v] != poss[v]) f = 0;
        }
        if (f) { runIt = false,mWin[0]++; break; }
    }

    for (int u = 3; u < 6; u++) {
        poss[u-3] = allPlayer[u].mPos;
    }
    std::sort(poss, poss + 3);
    for (int u = 1; u < 8; u++) {
        f = 1;
        for (int v = 0; v < 3; v++) {
            if (finishState[u][v] != poss[v]) f = 0;
        }
        if (f) { runIt = false, mWin[1]++; break; }
    }

    return gameRun = runIt;
}

void Game::afterGmProcessEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            mWindow.close();
        case sf::Event::KeyPressed:
             mallReset();

        }
    }
}

void Game::afterGmUpdate(sf::Time)
{
    if (!turn)
        allPlayer[0].setPosition(400.f, 400.f);
    else
        allPlayer[3].setPosition(400.f, 400.f);
    textOne1.setString("Press enter to continue playing");
    textOne1.setPosition(240.f, 480.f);
   
   
}



void  Game::mallReset() {
    for (int u = 0; u < 6; u++) mMove[u] = false;
    allPlayer[6].mPos= 6;
    for (int u = 0; u < 3; u++) allPlayer[u].mPos=u;
    for (int u = 3; u < 6; u++) allPlayer[u].mPos= u + 3;

    for (int u = 0; u < 3; u++) allPlayer[u].setPosition(mInitial[u]);
    for (int u = 3; u < 6; u++) allPlayer[u].setPosition(mInitial[u + 3]);
    allPlayer[6].setPosition(mInitial[9]);
    preFirst=1-preFirst,turn=preFirst;
    mPing = false, gameRun = true;
}

int Game::mWin[2] = {};
int Game::preFirst = 1;