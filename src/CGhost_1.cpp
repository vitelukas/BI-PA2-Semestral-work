#include "CGhost_1.hpp"
using namespace std;
using namespace std::chrono;

CGhost_1::CGhost_1() 
    : CGhost()
{
    m_Character = '&';
    m_EntityLook = 5;
}

void CGhost_1::decideMoveDirection(CMap& gameMap, const CPlayer& player) {
	size_t nextRow, nextCol;

	findShortestPath(gameMap , player, nextRow, nextCol);

    if (nextRow < m_Position.first)
        mvUp(gameMap);
    else if (nextRow > m_Position.first)
        mvDown(gameMap);
    else if (nextCol < m_Position.second)
        mvLeft(gameMap);
    else if (nextCol > m_Position.second)
        mvRight(gameMap);
    else
        CEntity::decideMoveDirection(gameMap);
}

void CGhost_1::findShortestPath(CMap& gameMap, const CPlayer& player, size_t &nextRow, size_t &nextCol) {
    // Perform BFS to find the shortest path to the player
    vector<vector<bool>> visited(gameMap.m_Height, vector<bool>(gameMap.m_Width, false));
    vector<vector<pair<size_t, size_t>>> parent(gameMap.m_Height, vector<pair<size_t, size_t>>(gameMap.m_Width, make_pair(SIZE_MAX, SIZE_MAX)));
    char futureDir = 'n';

    do {
        queue<pair<size_t, size_t>> q;

        q.push(m_Position);
        visited[m_Position.first][m_Position.second] = true;

        while (!q.empty()) {
            pair<size_t, size_t> current = q.front();
            q.pop();

            if (current == player.m_Position)
                break;

            // Check adjacent cells
            vector<pair<size_t, size_t>> neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (const auto& neighbor : neighbors) {
                size_t x = current.second + neighbor.second;
                size_t y = current.first + neighbor.first;

                if ( !CEntity::checkIfCollisions(gameMap, {y, x}) && !visited[y][x] ) {
                    q.push({y, x});
                    visited[y][x] = true;
                    parent[y][x] = current;
                }
            }
        }

        // If the queue is empty and player's position not reached, break the loop
        if (q.empty()) {
            nextRow = m_Position.first;
            nextCol = m_Position.second;
            break;
        }

        // Trace back the path from player to ghost
        vector<pair<size_t, size_t>> path;
        pair<size_t, size_t> current = player.m_Position;
        while (current != m_Position) {
            path.push_back(current);
            current = parent[current.first][current.second];
        }

        nextRow = path.back().first;
        nextCol = path.back().second;

        // Reset the temporary variables
        visited.assign(gameMap.m_Height, vector<bool>(gameMap.m_Width, false));
        parent.assign(gameMap.m_Height, vector<pair<size_t, size_t>>(gameMap.m_Width, make_pair(SIZE_MAX, SIZE_MAX)));
        path.clear();

        // Add the futurePosition into the visited in case it won't be valid (the direction to move towards this position is banned)
        visited[nextRow][nextCol] = true;

        pair<size_t, size_t> futurePos = make_pair(nextRow, nextCol);
        futureDir = determineDirection(futurePos);

    } while (!checkDirectionOK(futureDir));
}