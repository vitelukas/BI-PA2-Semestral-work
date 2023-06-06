#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <ncurses.h>
#include <climits>
#include <stdexcept>
#pragma once

using namespace std;

class CMap {
	public:
		CMap();

		void loadMap(const string & );

		void transformMap(char, size_t, size_t);

		void printMap();

	private:
		size_t m_Height, m_Width;
		char m_CoinCharr;
		vector<vector<char>> m_CharMap;
		unordered_map<char, char> m_AsciiToSymbolMap;
		pair<size_t, size_t> m_TeleportIn, m_TeleportOut;
		friend class CGame;
		friend class CEntity;
		friend class CPlayer;
		friend class CGhost_1;
		friend class CGhost_2;
		friend class CGhost_3;
};