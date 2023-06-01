#include "CGame.hpp"
using namespace std;

CGame::CGame() {
    m_GameIsDone = false;
    m_ScoreToWin = 0;
}

void CGame::run() {
    m_Map.loadMap("examples/main_map.txt");
    m_Map.showMap();
    for (int y = 0; y < m_Map.m_Height; y++) {
        for (size_t x = 0; x < m_Map.m_CharMap[y].size(); x++) {
            char entity = m_Map.m_CharMap[y][x];
            setEntities(entity, y, x);
        }
    }

    while( !m_GameIsDone ) {
        update();
        m_Player.move(m_Map);
    }
    
    return;
}

void CGame::update() {
    mvprintw(30, 0, "Score: %d", m_Player.m_Score);
    mvprintw(31, 0, "Lifes: %d", m_Player.m_Lifes);
    mvprintw(32, 0, "Score to win: %d", m_ScoreToWin);
    
    refresh();

    m_GameIsDone = m_Player.m_Score == m_ScoreToWin;

    //~ reloadMap();
}

void CGame::reloadMap() {
    m_Map.showMap();
}

void CGame::setEntities(char entity, int y, int x) {
    //~ auto it = m_Map.m_AsciiToSymbolMap.find(entity);
    //~ entity = it->second;
    switch (entity) {
        case 'O':
            m_Player.m_Position = {y, x};
            m_Player.m_Character = 'O';
            break;
        case '&':
            m_Ghost_1.m_Position = {y, x};
            break;
        case '@':
            m_Ghost_2.m_Position = {y, x};
            break;
        case '0':
            m_Ghost_3.m_Position = {y, x};
            break;
        case '.':
            ++m_ScoreToWin;
            break;
        default:
            break;
    }
}
