#include "CGame.hpp"
using namespace std;
using namespace std::chrono;

CGame::CGame() 
    : m_GameMode(1), m_GameIsDone(false), m_ScoreToWin(0), m_EatenGhosts(0), m_MapFile("examples/maps/main_map.txt")
{
    m_Ghosts.emplace_back(std::make_shared<CGhost_1>(5));
    m_Ghosts.emplace_back(std::make_shared<CGhost_2>(6));
    m_Ghosts.emplace_back(std::make_shared<CGhost_3>(7));
}

void CGame::run(const CGameMode &gameMode) {
    initializeGame(gameMode);

    // Move the entities until the game is finished
    while ( !m_GameIsDone ) {
        updateGameState(0);
        m_Player.move(m_Map);

        for (auto ghost : m_Ghosts) {
            ghost->move(m_Map, m_Player);
        }
    }

    // If the game ended and the player still has some lives left,
    // then he must have won
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

    m_Map.loadMap(m_MapFile);

    setGameConfig(gameMode);

    // Go through the whole map and take care of each tile
    // -> check the tile, if it's an entity, set it's values, etc.
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

    // Choose the type of collision handler based on the current game state (normal / berserk)
    berserkActive ? handleBerserkCollision() : handleGhostCollision();

    // Update the player's stats
    mvprintw(m_Map.m_Height + 1, 0, "Score: %d", m_Player.m_Score);
    mvprintw(m_Map.m_Height + 2, 0, "Lives: %d", m_Player.m_Lives);

    // Check if the player has won or is dead
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

    // After the is a collision between the player and a ghost,
    // set all entities into their initial positions and reset their directions
    setEntityAfterCollision();

    // Give a player a little time to react after a collision
    napms(600);
}

int CGame::checkGhostCollision() {
    // Vector of positions and integers, representing to which ghost does the position belong to 
    vector< pair< pair<size_t,size_t>, int>> ghostsAdjacentPositions;
    vector< pair<size_t,size_t>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
    //                                            UP     DOWN    LEFT     RIGHT   SAME

    int whichGhost = 1;
    // Make a vector of ghost's all possible adjacent positions
    // Also, keep track of which ghost the current position belongs to
    for (const auto &ghost : m_Ghosts) {
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
                                    //   -> return the id of the ghost in the collision
    }

    // There is no collision
    return 0;
}

// If no specific id of an entity was sent to the method,
// then set the arugment to the default value -1 == set all entities
void CGame::setEntityAfterCollision(int whichEntity) {
    vector<CEntity*> entities;
    entities.push_back(&m_Player);
    entities.push_back(m_Ghosts[0].get());
    entities.push_back(m_Ghosts[1].get());
    entities.push_back(m_Ghosts[2].get());

    int counter = -1;
    // Go through all entities and check if they are supposed to be set
    for (auto entity : entities) {
        counter++;
        // Check if the entity should be set or not based on the [in]param of the method
        // Skip the entity if it is not supposed to be set
        if (counter != whichEntity && whichEntity != -1)
            continue;

        size_t y = entity->m_Position.first;
        size_t x = entity->m_Position.second;
        entity->m_Direction = 'n';
        entity->m_Position = entity->m_InitialPosition;
        // Refresh the tile after removing the entity from it
        char tile = m_Map.m_CharMap[y][x];
        entity->formatTile(tile);
        mvaddch(y, x, tile);
    }
}

void CGame::handleBerserkCollision() {

    if ( int numOfGhost = checkGhostCollision() ) {
        // Add score points to the player's score,
        // and multiply it by number of eaten ghosts in one berserk run
        // If the player has eaten all the ghosts, don't add any more score points
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
    int slowGhost = m_Ghosts[0]->m_GhostSlower;
    attron(A_REVERSE);
    mvprintw(y, x, "Berserk mode active");
    attroff(A_REVERSE);
    reloadMap();

    // Kep track of the berserk mode duration
    auto prevTime    = m_Player.m_PreviousTime = steady_clock::now();
    auto curTime     = m_Player.m_CurrentTime  = steady_clock::now();
    auto elapsedTime = duration_cast<milliseconds>(curTime - prevTime);

    // Swap the ghosts direction to go back,
    // and set different color for ghosts, so that the player can see he can eat them
    for (auto ghost : m_Ghosts) {
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
        for (auto ghost : m_Ghosts) {
            ghost->CGhost::move(m_Map, m_Player);
        }

        // Update the current time spent in the berserk mode 
        curTime = steady_clock::now();
        elapsedTime = duration_cast<milliseconds>(curTime - prevTime);
    }

    move(y, x);
    clrtoeol(); // Clear the 'berserk mode active' text


    for (auto ghost : m_Ghosts) {
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
            m_Ghosts[0]->m_Position = m_Ghosts[0]->m_InitialPosition = {y, x};
            m_Ghosts[0]->m_Character = m_Map.m_AsciiToSymbolMap['&'];
            break;
        case '@':
            m_Ghosts[1]->m_Position = m_Ghosts[1]->m_InitialPosition = {y, x};
            m_Ghosts[1]->m_Character = m_Map.m_AsciiToSymbolMap['@'];
            break;
        case '0':
            m_Ghosts[2]->m_Position = m_Ghosts[2]->m_InitialPosition = {y, x};
            m_Ghosts[2]->m_Character = m_Map.m_AsciiToSymbolMap['0'];
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

    for (auto ghost : m_Ghosts) {
        ghost->m_GhostSlower = gameMode.m_GhostSpeed;
        ghost->m_Speed = milliseconds(gameMode.m_EntitySpeed);
    }

    m_Player.m_Speed = milliseconds(gameMode.m_EntitySpeed);
    m_Player.m_BerserkDuration = milliseconds(gameMode.m_BerserkerDuration);
    m_Player.m_Lives = gameMode.m_PlayerLives;
}
