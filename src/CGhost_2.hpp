#include "CGhost.hpp"
#include <queue>

#pragma once

/**
 * @class CGhost_2
 * @brief A class representing a specific type of ghost in the game - Inky.
 *
 * This class extends the base CGhost class and implements the behavior of another type of ghost.
 */
class CGhost_2 : public CGhost {
	public:
		/**
		 * @brief Default constructor for CGhost_3.
		 * @param entityLook Integer defining the number of coloring for the entity
		 */
		CGhost_2(int entityLook);

	protected:
		/**
		 * @brief Overrided method to determine the next move direction for the ghost based on a shortest path algorithm
		 * and a prediction of the player's movement.
		 * @param gameMap The game map.
		 * @param player The player entity.
		 * 
		 * Also handles the case when the position remains the same by making a random move, so that the ghost doesn't just stand on one place.
		 */
		virtual void decideMoveDirection(CMap& gameMap, const CEntity& player) override;

	private:
		/**
		 * @brief Finds the shortest path from the ghost to the predicted future position of the player.
		 * @param gameMap The game map.
		 * @param player The player entity.
		 * @param nextRow Reference to a size_t variable to store the next row position on the path.
		 * @param nextCol Reference to a size_t variable to store the next column position on the path.
		 * 
		 * This method uses the breadth-first search (BFS) algorithm to find the shortest path from the ghost's
		 * current position to the predicted future position of the player on the game map.
		 */
		void findShortestPath(CMap& gameMap, const CEntity& player, size_t& nextRow, size_t& nextCol);

	private:

};