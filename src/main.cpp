#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ncurses.h>
#include "CMainMenu.hpp"

using namespace std;

int main() {
	CMainMenu menu;
	initscr();

	// Show initial dialog info
	menu.run();

	endwin();
}