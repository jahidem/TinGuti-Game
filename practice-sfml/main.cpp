#include "main.h"

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	Menu *menu= new Menu();
	int pressed= menu->run();
	while (pressed != 2) {
		if (pressed == 0) {
			Game game;
			game.run();
		}std::cout << "run";
		//else if (pressed == 1) 
		delete menu;
		menu = new Menu();
		pressed = menu->run();
	}

}