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

		void showLeaderboard() const;

		void makeEntry(int) const;

		std::string getPlayerName() const;
	
	private:
		std::string m_FileLocation;
		// std::map<int, int> m_PositionScore;
};