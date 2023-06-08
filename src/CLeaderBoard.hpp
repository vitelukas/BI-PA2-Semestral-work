#include <string>
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>

#pragma once

class CLeaderBoard {
	public:
        CLeaderBoard();

		void showLeaderboard();

		void makeEntry(int);

		std::string getPlayerName();
	
	private:
		std::string m_FileLocation;
		// std::map<int, int> m_PositionScore;
};