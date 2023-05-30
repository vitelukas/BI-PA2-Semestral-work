#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <ncurses.h>
#pragma once

using namespace std;

class CMap {
	public:
		CMap();

		void loadMap ( const string & );

		void showMap ();

	private:
		int m_Height, m_Width;
		vector<vector<char>> m_CharMap;
		unordered_map<char, char> m_AsciiToSymbolMap;
};