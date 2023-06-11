#include <stdio.h>
#include <ncurses.h>
#include "CMainMenu.hpp"

using namespace std;

void cleanUp();

int main() {
	// Set up the initial attributes for the ncurses
	initscr();
    curs_set(0);
	cbreak();
    noecho();
	if (has_colors())
		start_color();

	// Set the background of the program to the terminal's default background
	if (assume_default_colors(-1, -1) == OK) {
		// Enable the use of the default terminal colors for color pairs 
        use_default_colors();
    }

	int again = 1;
	while (again) {
        try {
            CMainMenu mainMenu;
            again = mainMenu.run(again);
        } catch (const runtime_error& e) {
			cleanUp();
            cerr << "An error occurred while executing the code: " << e.what() << endl;
			return 1;
        } catch (...) {
			cleanUp();
            cerr << "There was an unknown error while running the program." << endl;
			return 1;
        }
    }

	cleanUp();
	return 0;
}

void cleanUp() {
	clear();
	delwin(stdscr);
	endwin();
}