#include "CMap.hpp"
using namespace std;

CMap::CMap()
    // Height and width will be set while loading the map from a file
    : m_Height(0), m_Width(0), m_CoinCharr('.'), m_CharMap() {
    m_TeleportIn = m_TeleportOut = make_pair(SIZE_MAX, SIZE_MAX);
    m_AsciiToSymbolMap = {
        {'#', '#'},
        {'p', 'O'},
        {'&', '&'},
        {'@', '@'},
        {'0', '0'},
        {'B', 'B'},
        {'.', '.'},
        {'T', 'T'},
    };

    init_pair(1, COLOR_BLUE, COLOR_BLUE);    // wall default color
    init_pair(2, COLOR_YELLOW, -1);          // coinf default color 		(-1 == use the default color for background)
    init_pair(3, COLOR_RED, -1);             // Cherry default color
    init_pair(4, COLOR_BLACK, COLOR_YELLOW); // Player default color
    init_pair(5, COLOR_BLACK, COLOR_RED);    // Ghost_1 default color
    init_pair(6, COLOR_BLACK, COLOR_CYAN);   // Ghost_2 default color
    init_pair(7, COLOR_BLACK, COLOR_WHITE);  // Ghost_3 default color
    init_pair(8, COLOR_BLACK, COLOR_GREEN);  // berserk mode ghost default color
}

void CMap::loadMap(const string &fileName) {
    m_CharMap.clear();
    m_TeleportIn = m_TeleportOut = make_pair(SIZE_MAX, SIZE_MAX);
    ifstream mapFile(fileName);

    if (!mapFile.is_open()) {
        cerr << "Error while opening the map file!" << endl;
        throw runtime_error("Failed to open the map file.");
    }

    // Load the map from the file into the map structure variable
    string line;
    while (getline(mapFile, line)) {
        vector<char> mapRow;
        for (char c : line) {
            mapRow.push_back(c);
        }
        m_CharMap.push_back(mapRow);
    }

    mapFile.close();

    // Set the map height and width based on the size of the map loaded from the file
    if (!m_CharMap.empty()) {
        m_Height = m_CharMap.size();
        m_Width = m_CharMap[0].size();
    }

    checkMapValidity();
}

void CMap::printMap() const {
    clear();

    size_t maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    // Check if the map can fit into the screen, throw an exception if not
    if (m_Height > maxY || m_Width > maxX) {
        cerr << "Error while printing the map file!" << endl;
        throw runtime_error("Cannot show map - map is bigger than the screen.");
    }

    // Print the map into the screen and color the individual tiles / entities accordingly
    for (size_t y = 0; y < m_Height; y++) {
        for (size_t x = 0; x < m_CharMap[y].size(); x++) {
            char ch = m_CharMap[y][x];
            switch (ch) {
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

// Transform the original map according to the the user specified symbols set in the m_AsciiToSymbolMap attribute
void CMap::transformMap(char tile, size_t y, size_t x) {
    auto it = m_AsciiToSymbolMap.find(tile);

    if (it != m_AsciiToSymbolMap.end())
        m_CharMap[y][x] = it->second;
    else
        m_CharMap[y][x] = tile;
}

bool CMap::checkMapValidity() {
    bool pFlag, g1Flag, g2Flag, g3Flag;
    pFlag = g1Flag = g2Flag = g3Flag = false;
    std::unordered_map<char, int> entityCounts;

    if (m_CharMap.empty()) {
        cerr << "Error while loading the map file!" << endl;
        throw runtime_error("Wrong format of the map: the map is empty!");
    }

    for (size_t y = 0; y < m_Height; y++) {
        for (size_t x = 0; x < m_CharMap[y].size(); x++) {
            char tile = m_CharMap[y][x];
            if ((m_AsciiToSymbolMap.find(tile) == m_AsciiToSymbolMap.end()) && !isspace(tile)) {
                cerr << "Error while loading the map file!" << endl;
                throw runtime_error("Wrong format of the map: unspecified char/entity");
            } else {
                // Increment the count of the entity
                entityCounts[tile]++;
            }
        }
    }

    // Check if entities are present in the map and if there are duplicates or not
    pFlag = entityCounts['p'] == 1;
    g1Flag = entityCounts['0'] == 1;
    g2Flag = entityCounts['&'] == 1;
    g3Flag = entityCounts['@'] == 1;

    if (!(pFlag && g1Flag && g2Flag && g3Flag)) {
        cerr << "Error while loading the map file!" << endl;
        throw runtime_error("Wrong format of the map: wrong entity count");
    }

    return true;
}