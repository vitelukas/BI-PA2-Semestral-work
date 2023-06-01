#include "CMap.hpp"
using namespace std;


CMap::CMap() 
	:m_CharMap()
{
	m_Height = 0;
	m_Width = 0;
	m_TeleportIn = m_TeleportOut = {INT_MAX, INT_MAX};
	m_AsciiToSymbolMap = {
		{'#', '#'},
        {'.', '.'},
        {'p', 'O'},
        {'&', '&'},
        {'@', '@'},
        {'0', '0'},
        {'B', 'B'},
	};
}

void CMap::loadMap(const string &fileName) {
    ifstream mapFile(fileName);

    if ( !mapFile.is_open() ) {
		cerr << "Error while opening the map file!" << endl;
		throw std::runtime_error("Failed to open the map file.");
	}
	
	string line;
	int x, y;
	x = y = 0;
	while (getline(mapFile, line)) {
		vector<char> mapRow;
		for (char c : line) {
			auto it = m_AsciiToSymbolMap.find(c);
			
			if ( c == 'T') {
				endwin();
				if ( m_TeleportIn == make_pair(INT_MAX, INT_MAX))
					m_TeleportIn = make_pair(y, x);
				m_TeleportOut = make_pair(y, x);
			}
				

			if (it != m_AsciiToSymbolMap.end()) {
				mapRow.push_back(it->second);
			} else {
				// Char in the config map file is not mapped -> leave the original char
				mapRow.push_back(c);
			}
			x++;
		}
		m_CharMap.push_back(mapRow);
		x = 0;
		y++;
	}

	mapFile.close();

	m_Height = m_CharMap.size();
	m_Width = m_CharMap[0].size();
}

void CMap::showMap () {
	clear();

	// init_color(COLOR_BLUE, 000, 000, 600 );
	init_pair(1, COLOR_BLUE, COLOR_BLUE);
	init_pair(2, COLOR_YELLOW, -1); // Use the default color for background
	init_pair(3, COLOR_RED, -1);
	init_pair(4, COLOR_YELLOW, -1);

	int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

	// Check if the map can fit the screen
    if (m_Height > maxY || m_Width > maxX) {
        endwin();
        cerr << "Cannot show map - map is bigger than the screen." << endl;
        return;
    }

	for (int y = 0; y < m_Height; y++) {
        for (size_t x = 0; x < m_CharMap[y].size(); x++) {
			switch (m_CharMap[y][x]) {
				case '#':
					attron(COLOR_PAIR(1)); 
					mvaddch(y, x, m_CharMap[y][x]);
					attroff(COLOR_PAIR(1));
					break;
            	case '.': 
					attron(COLOR_PAIR(2));
					mvaddch(y, x, m_CharMap[y][x]);
					attroff(COLOR_PAIR(2));
					break;
				case 'B':
					attron(COLOR_PAIR(3));
					mvaddch(y, x, m_CharMap[y][x]);
					attroff(COLOR_PAIR(3));
					break;
				case 'O':
					attron(COLOR_PAIR(4));
					mvaddch(y, x, m_CharMap[y][x]);
					attroff(COLOR_PAIR(4));
					break;
				case 'T':
					attron(A_INVIS);
					mvaddch(y, x, m_CharMap[y][x]);
					attroff(A_INVIS);
					break;
				default:			
                	mvaddch(y, x, m_CharMap[y][x]);
					break;
            }
        }
    }

    refresh();
} 