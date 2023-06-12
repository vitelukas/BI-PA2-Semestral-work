#include "CGhost_1.hpp"
using namespace std;
using namespace std::chrono;

CGhost_1::CGhost_1(int entityLook) 
	: CGhost(entityLook)
{
    m_Character = '&';
    m_EntityLook = 5;
}

void CGhost_1::decideMoveDirection(CMap &gameMap, const CEntity &player) {
	size_t nextRow, nextCol;

    // Perform BFS to find the shortest path towards the player
	findShortestPath(gameMap , player, nextRow, nextCol);

    // Determine the next move based on the algorithm's found position to which the ghost should move
    if (nextRow < m_Position.first)
        mvUp(gameMap);
    else if (nextRow > m_Position.first)
        mvDown(gameMap);
    else if (nextCol < m_Position.second)
        mvLeft(gameMap);
    else if (nextCol > m_Position.second)
        mvRight(gameMap);
    else
        CGhost::decideMoveDirection(gameMap, player);
}

void CGhost_1::findShortestPath(CMap &gameMap, const CEntity &player, size_t &nextRow, size_t &nextCol) {
    vector<vector<bool>> visited(gameMap.m_Height, vector<bool>(gameMap.m_Width, false));
    vector<vector<pair<size_t, size_t>>> parent(gameMap.m_Height, vector<pair<size_t, size_t>>(gameMap.m_Width, make_pair(SIZE_MAX, SIZE_MAX)));
    char futureDir = 'n';

    // Repeat the BFS algorithm until we find a valid path towards the player
    // (if the current found path would mean that the ghost would have to turn around -> search again)
    do {
        queue<pair<size_t, size_t>> q;

        q.push(m_Position);
        visited[m_Position.first][m_Position.second] = true;

        while (!q.empty()) {
            pair<size_t, size_t> current = q.front();
            q.pop();

            // Break the algorithm if we found the shortest path to the player's position
            if (current == player.getPosition())
                break;

            // Check adjacent cells
            vector<pair<size_t, size_t>> neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (const auto& neighbor : neighbors) {
                size_t x = current.second + neighbor.second;
                size_t y = current.first + neighbor.first;

                // Check if all the adjacent cells are valid and the ghost can move there
                if ( !CEntity::checkIfCollisions(gameMap, {y, x}) && !visited[y][x] ) {
                    q.push({y, x});
                    visited[y][x] = true;
                    parent[y][x] = current;
                }
            }
        }

        // If the queue is empty and player's position was not reached, break the loop
        if (q.empty()) {
            // Set the next position to the current position so that the ghost will move in his current direction
            nextRow = m_Position.first;
            nextCol = m_Position.second;
            break;
        }

        // Trace back the path from the player's position to the ghost
        vector<pair<size_t, size_t>> path;
        pair<size_t, size_t> current = player.getPosition();
        while (current != m_Position) {
            path.push_back(current);
            current = parent[current.first][current.second];
        }

        nextRow = path.back().first;
        nextCol = path.back().second;

        // (Re)set the temporary variables in case we would have to perform BFS again
        visited.assign(gameMap.m_Height, vector<bool>(gameMap.m_Width, false));
        parent.assign(gameMap.m_Height, vector<pair<size_t, size_t>>(gameMap.m_Width, make_pair(SIZE_MAX, SIZE_MAX)));
        path.clear();

        // Add the futurePosition into the visited in case it won't be valid ( == the direction to move towards this position is banned)
        visited[nextRow][nextCol] = true;

        pair<size_t, size_t> futurePos = make_pair(nextRow, nextCol);
        futureDir = determineDirection(futurePos);

    } while (!checkDirectionOK(futureDir));
}