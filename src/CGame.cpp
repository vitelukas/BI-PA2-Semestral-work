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
    reloadMap();

    handleGhostCollision();

    mvprintw(m_Map.m_Height + 1, 0, "Score: %d", m_Player.m_Score);
    mvprintw(m_Map.m_Height + 2, 0, "Lifes: %d", m_Player.m_Lifes);
    
    m_GameIsDone = (m_Player.m_Score == m_ScoreToWin) || (m_Player.m_Lifes == 0);

    reloadMap();
}

void CGame::reloadMap() {  
    // Only refreshes the changed cells, not the whole screen
    refresh();
}

void CGame::setEntities(char entity, size_t y, size_t x) {
    switch (entity) {
        case 'p':
            m_Player.m_Position = m_Player.m_InitialPosition = {y, x};
            m_Player.m_Character = m_Map.m_AsciiToSymbolMap['p'];
            break;
        case '&':
            m_Ghost_1.m_Position = m_Ghost_1.m_InitialPosition = {y, x};
            m_Ghost_1.m_Character = m_Map.m_AsciiToSymbolMap['&'];
            break;
        case '@':
            m_Ghost_2.m_Position = m_Ghost_2.m_InitialPosition = {y, x};
            m_Ghost_2.m_Character = m_Map.m_AsciiToSymbolMap['@'];
            break;
        case '0':
            m_Ghost_3.m_Position = m_Ghost_3.m_InitialPosition = {y, x};
            m_Ghost_3.m_Character = m_Map.m_AsciiToSymbolMap['0'];
            break;
        case '.':
            ++m_ScoreToWin;
            m_Map.m_CoinCharr = m_Map.m_AsciiToSymbolMap['.'];
            break;
        case 'B':
            ++m_ScoreToWin;
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

void CGame::handleGhostCollision() {

    // If there is no collision between the player and a ghost --> return
    if ( !checkGhostCollision() )
        return;
    
    m_Player.m_Lifes--;
    m_Player.m_PrevDirection = 'n';

    setEntityAfterCollision();

    // Give a player a little time to react after a collision
    napms(600);
}

bool CGame::checkGhostCollision() {
    const vector<CGhost*> ghosts = {&m_Ghost_1, &m_Ghost_2, &m_Ghost_3};
    vector<pair<size_t, size_t>> adjacentPositions;
    vector<pair<size_t, size_t>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    //                                            UP     DOWN    LEFT     RIGHT

    // Make a vector of ghosts all possible adjacent positions
    for (const auto &ghost : ghosts) {
        for (const auto& direction : directions) {
                size_t y = ghost->m_Position.first + direction.first;
                size_t x = ghost->m_Position.second + direction.second;
                adjacentPositions.push_back({y, x});
            }
    }

    // Check if the player is currently at any of the ghosts adjacent positions
    for (const auto& position : adjacentPositions) {
        if (m_Player.m_Position == position)
            return true;    // There is a collision between the player and a ghost
    }

    return false;
}

void CGame::setEntityAfterCollision() {
    vector<CEntity*> entities = {&m_Player, &m_Ghost_1, &m_Ghost_2, &m_Ghost_3};

    for (auto entity : entities) {
        size_t y = entity->m_Position.first;
        size_t x = entity->m_Position.second;
        entity->m_Direction = 'n';
        entity->m_Position = entity->m_InitialPosition;
        char tile = m_Map.m_CharMap[y][x];
        entity->formatTile(tile);
        mvaddch(y, x, tile);   
    }
}
