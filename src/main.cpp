#include <stdio.h>
#include <ncurses.h>
#include "CMainMenu.hpp"

using namespace std;

int main() {
	CMainMenu menu;
	initscr();

	menu.run();

	endwin();
}