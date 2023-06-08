#include "CGame.hpp"
using namespace std;
using namespace std::chrono;

CGame::CGame() {
    m_GameIsDone = false;
    m_ScoreToWin = 0;
}

void CGame::run() {
    initializeGame();

    while ( !m_GameIsDone ) {
        update();
        m_Player.move(m_Map);

        m_Ghost_1.move(m_Map, m_Player);

        m_Ghost_2.move(m_Map, m_Player);

        m_Ghost_3.move(m_Map, m_Player);
    }

    return;
}

void CGame::initializeGame() {
    clear();   
    m_Map.loadMap("examples/maps/main_map.txt");

    for (size_t y = 0; y < m_Map.m_Height; y++) {
        for (size_t x = 0; x < m_Map.m_CharMap[y].size(); x++) {
            char entity = m_Map.m_CharMap[y][x];
            setEntities(entity, y, x);
            m_Map.transformMap(entity, y, x );
        }
    }

    //todo include into game difficulty setting and delete from here ↓ 
    m_Ghost_1.m_Speed = m_Ghost_2.m_Speed = m_Ghost_3.m_Speed = m_Player.m_Speed;

    m_Map.printMap();
}

void CGame::update() {
    mvprintw(m_Map.m_Height + 1, 0, "Score: %d", m_Player.m_Score);
    mvprintw(m_Map.m_Height + 2, 0, "Lifes: %d", m_Player.m_Lifes);
    
    m_GameIsDone = m_Player.m_Score == m_ScoreToWin;

    //todo check collisions between the player and a ghost
    //todo if there was a collision set entities into the original places

    reloadMap();
}

void CGame::reloadMap() {  
    // Only refreshes the changed cells, not the whole screen
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
            m_Ghost_1.m_Character = m_Map.m_AsciiToSymbolMap['&'];
            break;
        case '@':
            m_Ghost_2.m_Position = {y, x};
            m_Ghost_2.m_Character = m_Map.m_AsciiToSymbolMap['@'];
            break;
        case '0':
            m_Ghost_3.m_Position = {y, x};
            m_Ghost_3.m_Character = m_Map.m_AsciiToSymbolMap['0'];
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