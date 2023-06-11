#include "CGame.hpp"
using namespace std;
using namespace std::chrono;

#define MAP_FILE "examples/maps/main_map.txt"

CGame::CGame() 
    : m_GameMode(1), m_GameIsDone(false), m_ScoreToWin(0), m_EatenGhosts(0)
{
}

void CGame::run(const CGameMode &gameMode) {
    initializeGame(gameMode);

    while ( !m_GameIsDone ) {
        updateGameState(0);
        m_Player.move(m_Map);

        m_Ghost_1.move(m_Map, m_Player);

        m_Ghost_2.move(m_Map, m_Player);

        m_Ghost_3.move(m_Map, m_Player);
    }

    if (m_Player.m_Lives)
        playerWon();
    else
        playerLost();
    refresh();    

    // Pause the game for a bit after the game ends
    napms(3000);

    return;
}

void CGame::initializeGame(const CGameMode &gameMode) {
    clear();   

    m_Map.loadMap(MAP_FILE);

    setGameConfig(gameMode);

    for (size_t y = 0; y < m_Map.m_Height; y++) {
        for (size_t x = 0; x < m_Map.m_CharMap[y].size(); x++) {
            char entity = m_Map.m_CharMap[y][x];
            setEntities(entity, y, x);
            m_Map.transformMap(entity, y, x );
        }
    }

    m_Map.printMap();
}

void CGame::updateGameState(int berserkActive) {
    reloadMap();

    if(m_Player.m_IsBerserk)
        goBerserk();

    berserkActive ? handleBerserkCollision() : handleGhostCollision();

    mvprintw(m_Map.m_Height + 1, 0, "Score: %d", m_Player.m_Score);
    mvprintw(m_Map.m_Height + 2, 0, "Lives: %d", m_Player.m_Lives);
    
    m_GameIsDone = (m_Player.m_Score >= m_ScoreToWin) || (m_Player.m_Lives == 0);

    reloadMap();
}

void CGame::reloadMap() const {  
    // Only refreshes the changed cells, not the whole screen
    refresh();
}

void CGame::handleGhostCollision() {

    // If there is no collision between the player and a ghost --> return
    if ( !checkGhostCollision() )
        return;
    
    m_Player.m_Lives--;
    m_Player.m_PrevDirection = 'n';

    setEntityAfterCollision();

    // Give a player a little time to react after a collision
    napms(600);
}

int CGame::checkGhostCollision() {
    const vector<CGhost*> ghosts = {&m_Ghost_1, &m_Ghost_2, &m_Ghost_3};
    // Vector of positions and integers, representing to which ghost does the position belong to 
    vector< pair< pair<size_t,size_t>, int>> ghostsAdjacentPositions;
    vector< pair<size_t,size_t>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
    //                                            UP     DOWN    LEFT     RIGHT   SAME

    int whichGhost = 1;
    // Make a vector of ghosts all possible adjacent positions
    for (const auto &ghost : ghosts) {
        for (const auto& direction : directions) {
                size_t y = ghost->m_Position.first + direction.first;
                size_t x = ghost->m_Position.second + direction.second;
                ghostsAdjacentPositions.push_back({{y, x}, whichGhost});
            }
        whichGhost++;
    }

    // Check if the player is currently at any of the ghosts adjacent positions
    for (const auto& adjacent : ghostsAdjacentPositions) {
        if (m_Player.m_Position == adjacent.first)
            return adjacent.second; // There is a collision between the player and a ghost
                                    //   -> return the id of ghost in the collision
    }

    // There is no collision
    return 0;
}

// If no specific id of an entity was sent to the method,
// then set the arugment to the default value -1 == set all entities
void CGame::setEntityAfterCollision(int whichEntity) {
    vector<CEntity*> entities = {&m_Player, &m_Ghost_1, &m_Ghost_2, &m_Ghost_3};

    int counter = -1;
    for (auto entity : entities) {
        counter++;
        if (counter != whichEntity && whichEntity != -1)
            continue;

        size_t y = entity->m_Position.first;
        size_t x = entity->m_Position.second;
        entity->m_Direction = 'n';
        entity->m_Position = entity->m_InitialPosition;
        char tile = m_Map.m_CharMap[y][x];
        entity->formatTile(tile);
        mvaddch(y, x, tile);
    }
}

void CGame::handleBerserkCollision() {

    if ( int numOfGhost = checkGhostCollision() ) {
        if ( m_EatenGhosts < 3) {
            m_EatenGhosts++;
            m_ScoreToWin += 20 * m_EatenGhosts;
            m_Player.m_Score += 20 * m_EatenGhosts;
        }
        setEntityAfterCollision(numOfGhost);
    }
    
}

void CGame::goBerserk() {
    m_Player.m_IsBerserk = false;
    auto y = m_Map.m_Height + 2;
    auto x = m_Map.m_Width - 20;
    int slowGhost = m_Ghost_1.m_GhostSlower;
    attron(A_REVERSE);
    mvprintw(y, x, "Berserk mode active");
    attroff(A_REVERSE);
    reloadMap();

    auto prevTime    = m_Player.m_PreviousTime = steady_clock::now();
    auto curTime     = m_Player.m_CurrentTime  = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(curTime - prevTime);

    // Swap the ghosts direction to go back,
    // and set different color for ghosts, so that the player can see he can eat them
    const vector<CGhost*> ghosts = {&m_Ghost_1, &m_Ghost_2, &m_Ghost_3};
    for (auto ghost : ghosts) {
        ghost->m_EntityLook = 8;
        int numDir = ghost->m_DirectionsTable[ghost->m_Direction];
        ghost->m_Direction = ghost->m_BackDirections[numDir];

        // Slow the ghosts when entering the berserk mode
        ghost->m_Speed += milliseconds(slowGhost);
    }

    while ( elapsedTime < m_Player.m_BerserkDuration ) {
        updateGameState(1);

        m_Player.move(m_Map);

        // Move ghosts in random directions;
        m_Ghost_1.move(m_Map, m_Player);
        m_Ghost_2.move(m_Map, m_Player);
        m_Ghost_3.move(m_Map, m_Player);

        curTime = steady_clock::now();
        elapsedTime = duration_cast<milliseconds>(curTime - prevTime);
    }

    move(y, x);
    clrtoeol(); // Clear the berserk active text

    // Set back the default ghosts colors
    m_Ghost_1.m_EntityLook = 5;
    m_Ghost_2.m_EntityLook = 6;
    m_Ghost_3.m_EntityLook = 7;
    for (auto ghost : ghosts) {
        // Speed up the ghosts after the end of the berserk mode
        ghost->m_Speed -= milliseconds(slowGhost);
    }
    m_EatenGhosts = 0;
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

void CGame::playerWon() const {
    attron(A_STANDOUT);
    mvprintw(m_Map.m_Height + 4, m_Map.m_Width/2 - 4, "YOU WON!");
    attroff(A_STANDOUT);
}

void CGame::playerLost() const {
    attron(A_STANDOUT);
    mvprintw(m_Map.m_Height + 4, m_Map.m_Width/2 - 10, "YOU LOST, BETTER LUCK NEXT TIME.");
    attroff(A_STANDOUT);
}

void CGame::setGameConfig(const CGameMode &gameMode) {
    vector<CGhost*> ghosts = {&m_Ghost_1, &m_Ghost_2, &m_Ghost_3};

    for (auto ghost : ghosts) {
        ghost->m_GhostSlower = gameMode.m_GhostSpeed;
        ghost->m_Speed = milliseconds(gameMode.m_EntitySpeed);
    }

    m_Player.m_Speed = milliseconds(gameMode.m_EntitySpeed);
    m_Player.m_BerserkDuration = milliseconds(gameMode.m_BerserkerDuration);
    m_Player.m_Lives = gameMode.m_PlayerLives;
}
