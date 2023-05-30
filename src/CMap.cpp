#include "CMap.hpp"
using namespace std;


CMap::CMap() {
	m_Height = 0;
	m_Width = 0;
	m_CharMap = {};
	m_AsciiToSymbolMap = {
		{'#', '#'},
        {'.', '.'},
        {'p', 'O'},
	};
}

void CMap::loadMap(const string &fileName) {
	vector<vector<char>> map;
    ifstream mapFile(fileName);

    if (mapFile.is_open()) {
        string line;
        while (getline(mapFile, line)) {
            vector<char> mapRow;
            for (char c : line) {
                auto it = m_AsciiToSymbolMap.find(c);
                if (it != m_AsciiToSymbolMap.end()) {
                    mapRow.push_back(it->second);
                } else {
                    // Char in the conf map file is not mapped -> leave the original char
                    mapRow.push_back(c);
                }
            }
            map.push_back(mapRow);
        }

        mapFile.close();
    } else {
        cerr << "Error while opening the map file!" << endl;
    }

	m_Height = map.size();
	m_Width = map[0].size();
	m_CharMap = map;
}

void CMap::showMap () {
	clear();

	// init_color(COLOR_BLUE, 000, 000, 600 );
	init_pair(1, COLOR_BLUE, COLOR_BLUE);
	init_pair(2, COLOR_YELLOW, -1); // Use the default color for background

	int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

	// Check if the map can fit the screen
    if (m_Height > maxY || m_Width > maxX) {
        endwin();  // Ukončení režimu ncurses
        cerr << "Cannot show map - map is bigger than the screen." << endl;
        return;
    }

	for (int y = 0; y < m_Height; y++) {
        for (int x = 0; x < m_Width; x++) {
			if (m_CharMap[y][x] == '#') {
                attron(COLOR_PAIR(1)); 
                mvaddch(y, x, m_CharMap[y][x]);
                attroff(COLOR_PAIR(1)); 
            } else if (m_CharMap[y][x] == '.') {
				attron(COLOR_PAIR(2));
                mvaddch(y, x, m_CharMap[y][x]);
                attroff(COLOR_PAIR(2)); 
			}
			else {
                mvaddch(y, x, m_CharMap[y][x]);
            }
        }
    }

    refresh();
} 