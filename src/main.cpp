#include <stdio.h>
#include <ncurses.h>
#include "CMainMenu.hpp"

using namespace std;

int main() {
	initscr();
    curs_set(0);
	cbreak();
    noecho();

	CMainMenu menu;

	menu.run();

	endwin();
	return 0;
}