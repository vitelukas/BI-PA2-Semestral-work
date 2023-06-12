#include "CEntity.hpp"
#include "CPlayer.hpp"
#include <ctime>

#pragma once

/**
 * @class CGhost
 * @brief Ghost base class representing a ghost entity in the game.
 *
 * This class inherits from the CEntity class and provides functionality for a ghost entity.
 * It includes methods for moving the ghost, deciding the next move direction, handling collisions,
 * determining valid directions, and choosing random moves.
 */
class CGhost : public CEntity {
	public:
		/**
		 * @brief Default constructor for CGhost.
		 */
		CGhost(int entityLook);

	protected:
		
		/**
		 * @brief Moves the ghost on the game map.
		 * @param gameMap The game map.
		 * @param player The player entity.
		 * 
		 * This method moves the ghost on the game map according to its current direction.
		 * It handles the timing of the ghost's movement by checking the elapsed time.
		 * If there is a collision or the chosen direction is not valid, a random move is chosen.
		 * The ghost updates its direction after moving.
		 */
		virtual void move(CMap& gameMap, const CPlayer& player);

		/**
		 * @brief Overrides the base class's decideMoveDirection method to decide the next move of a ghost.
		 * @param gameMap The game map.
		 * @param player The player entity.
		 * 
		 * This method decides the next move direction for the ghost based on its current direction.
		 */
		virtual void decideMoveDirection(CMap& gameMap, const CEntity& player) override;

		/**
		 * @brief Overrides the base class's mvUp method.
		 * @param gameMap The game map.
		 * 
		 * Moves the ghost upwards on the game map.
		 */
		virtual void mvUp(CMap& gameMap) override;

		/**
		 * @brief Overrides the base class's mvDown method.
		 * @param gameMap The game map.
		 * 
		 * Moves the ghost downwards on the game map.
		 */
		virtual void mvDown(CMap& gameMap) override;

		/**
		 * @brief Overrides the base class's mvLeft method.
		 * @param gameMap The game map.
		 * 
		 * Moves the ghost to the left on the game map.
		 */
		virtual void mvLeft(CMap& gameMap) override;

		/**
		 * @brief Overrides the base class's mvRight method.
		 * @param gameMap The game map.
		 * 
		 * Moves the ghost to the right on the game map.
		 */
		virtual void mvRight(CMap& gameMap) override;

		/**
		 * @brief Checks if there are collisions with walls or corridors and if the future direction is valid.
		 * @param gameMap The game map.
		 * @param futurePosition The future position of the ghost.
		 * @return True if there are collisions, false otherwise.
		 * 
		 * This method checks if the ghost's future position will result in collisions with walls or corridors on the game map,
		 * and also if the ghost can move in the newly given direction.
		 * It also handles teleportation if the ghost reaches a teleportation tile.
		 */
		virtual bool checkIfCollisions(CMap& gameMap, std::pair<size_t, size_t> futurePosition);

		/**
		 * @brief Checks if the future direction is valid.
		 * @param futureDirection The future direction of the ghost.
		 * @return True if the direction is valid, false otherwise.
		 * 
		 * This method checks if the future direction of the ghost is valid by comparing it with the banned direction of the current direction.
		 * It ensures that the ghost does not move in the opposite direction.
		 * (ghosts cannot turn around and go backwards)
		 */
		bool checkDirectionOK(char futureDirection) const;

		/**
		 * @brief Determines the direction based on the future position.
		 * @param futurePos The future position of the ghost.
		 * @return The direction as a character ('w', 's', 'a', 'd', or the current direction).
		 * 
		 * This method determines the direction based on the future position of the ghost.
		 * It compares the future position with the current position to determine the direction.
		 */
		char determineDirection(std::pair<size_t, size_t> futurePos) const;

	private:
	
		/**
		 * @brief Chooses a random move for the ghost.
		 * @param gameMap The game map.
		 * 
		 * This method generates a pseudo-random direction based on the current time and selects a move accordingly.
		 * This method chooses a random move for the ghost, if it collides with a wall.
		 * This method is also utilised when the ghosts are in the frightened state,
		 * so that they run away from the player in random directions.
		 */
		void chooseRandomMove(CMap& gameMap);

	protected:
		unordered_map<char, int> m_BackDirections;	/**< A map of directions and their corresponding opposite directions. */
		unordered_map<int, char> m_DirectionsTable;	/**< A map of direction numbers and their corresponding characters. */
		int m_GhostSlower;							/**< The time interval for slowing down the ghost's movement. */
		friend class CGame;
};