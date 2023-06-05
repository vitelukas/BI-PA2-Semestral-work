#include "CGame.hpp"
using namespace std;
using namespace std::chrono;

CGame::CGame() {
    m_GameIsDone = false;
    m_ScoreToWin = 0;
}

void CGame::run() {
    initializeGame();

    while (!m_GameIsDone) {
        update();
        m_Player.move(m_Map);
        m_Ghost_1.move(m_Map);
    }

    return;
}

void CGame::initializeGame() {   
    m_Map.loadMap("examples/main_map.txt");

    for (size_t y = 0; y < m_Map.m_Height; y++) {
        for (size_t x = 0; x < m_Map.m_CharMap[y].size(); x++) {
            char entity = m_Map.m_CharMap[y][x];
            setEntities(entity, y, x);
            m_Map.transformMap(entity, y, x );
        }
    }
    
    m_Map.printMap();
}

void CGame::update() {
    mvprintw(m_Map.m_Height + 1, 0, "Score: %d", m_Player.m_Score);
    mvprintw(m_Map.m_Height + 2, 0, "Lifes: %d", m_Player.m_Lifes);
    mvprintw(30, 0, "Player position y,x: %zu, %zu", m_Player.m_Position.first, m_Player.m_Position.second);
    mvprintw(31, 0, "TPin position y,x: %zu, %zu", m_Map.m_TeleportIn.first, m_Map.m_TeleportIn.second);
    mvprintw(32, 0, "TPout position y,x: %zu, %zu", m_Map.m_TeleportOut.first, m_Map.m_TeleportOut.second);
    
    m_GameIsDone = m_Player.m_Score == m_ScoreToWin;

    reloadMap();
}

void CGame::reloadMap() {   
    refresh();
}

void CGame::setEntities(char entity, size_t y, size_t x) {
    switch (entity) {
        case 'p':
            m_Player.m_Position = {y, x};
            m_Player.m_Character = m_Map.m_AsciiToSymbolMap['p'];
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
            m_Map.m_CoinCharr = m_Map.m_AsciiToSymbolMap['.'];
            break;
        case 'T':
            if (m_Map.m_TeleportIn == make_pair(SIZE_MAX, SIZE_MAX))
                m_Map.m_TeleportIn = make_pair(y, x);
            else
                m_Map.m_TeleportOut = make_pair(y, x);
            break;
        default:
            break;
    }
}