#include <stdio.h>
#include <ncurses.h>
#include "CMainMenu.hpp"

using namespace std;

int main() {
	initscr();
    curs_set(0);
	cbreak();
    noecho();
	start_color();
	if (assume_default_colors(-1, -1) == OK) {
        use_default_colors();
    }


	CMainMenu menu;

	menu.run();

	endwin();
	return 0;
}