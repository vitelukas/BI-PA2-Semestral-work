#include <stdio.h>
#include <ncurses.h>
#include "CMainMenu.hpp"

using namespace std;

int main() {
	initscr();
    curs_set(0);
	cbreak();
    noecho();
	if (has_colors())
		start_color();

	if (assume_default_colors(-1, -1) == OK) {
        use_default_colors();
    }

	int again = 1;
	while (again) {
		timeout(-1);		
		CMainMenu mainMenu;

		again = mainMenu.run(again);
	}

	delwin(stdscr);
	endwin();
	return 0;
}