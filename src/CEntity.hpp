#include "CMap.hpp"
#include <algorithm>
#include <chrono>
#pragma once

/**
 * @class CEntity
 * @brief A base class representing a game entity.
 *
 * This class provides a base for game entities and includes methods for moving the entity,
 * deciding the move direction, handling collisions, and formatting tiles.
 * It also includes member variables for position, speed, direction, character representing the entity, and entity look.
 */
class CEntity {
	public:
		/**
		 * @brief Default constructor for CEntity.
		 */
		CEntity();

		/**
		 * @brief Virtual destructor for CEntity.
		 */
		virtual ~CEntity() {}

		/**
		 * @brief Gets the current position of the entity.
		 * @return The current position of the entity as a pair of coordinates (y, x).
		 */
		std::pair<size_t, size_t> getPosition() const;

		/**
		 * @brief Gets the current direction of the entity.
		 * @return The current direction of the entity.
		 */
		char getDirection() const;

	protected:
		/**
		 * @brief Pure virtual method for deciding the move direction of an entity.
		 *
		 * This method is responsible for deciding the move direction of the entity
		 * based on the game map and other entities.
		 *
		 * @param gameMap The game map.
		 * @param entity The entity to interact with.
		 */
		virtual void decideMoveDirection(CMap& gameMap, const CEntity& entity) = 0;

		/**
		 * @brief Pure virtual method for moving the entity upwards.
		 *
		 * This method is responsible for moving the entity upwards on the game map.
		 *
		 * @param gameMap The game map.
		 */
		virtual void mvUp(CMap& gameMap) = 0;

		/**
		 * @brief Pure virtual method for moving the entity downwards.
		 *
		 * This method is responsible for moving the entity downwards on the game map.
		 *
		 * @param gameMap The game map.
		 */
		virtual void mvDown(CMap& gameMap) = 0;

		/**
		 * @brief Pure virtual method for moving the entity to the left.
		 *
		 * This method is responsible for moving the entity to the left on the game map.
		 *
		 * @param gameMap The game map.
		 */
		virtual void mvLeft(CMap& gameMap) = 0;

		/**
		 * @brief Pure virtual method for moving the entity to the right.
		 *
		 * This method is responsible for moving the entity to the right on the game map.
		 *
		 * @param gameMap The game map.
		 */
		virtual void mvRight(CMap& gameMap) = 0;

		/**
		 * @brief Checks if there are any collisions with walls or corridors.
		 *
		 * This method checks if the entity's future position will result in a collisions with walls or corridors on the game map.
		 * It also handles teleportation if the entity reaches a teleportation tile.
		 *
		 * @param gameMap The game map.
		 * @param futurePosition The future position of the entity.
		 * @return True if there are collisions, false otherwise.
		 */
		virtual bool checkIfCollisions(CMap& gameMap, std::pair<size_t, size_t> futurePosition);

		/**
		 * @brief Checks if there is a collision with a wall.
		 *
		 * This method checks if the entity's position will result in a collision with a wall on the game map,
		 * or if the position is out of the map bounds.
		 *
		 * @param gameMap The game map.
		 * @param position The position of the entity.
		 * @return True if there is a collision with a wall, false otherwise.
		 */
		bool wallCollision(const CMap& gameMap, std::pair<size_t, size_t> position) const;

		/**
		 * @brief Checks if there is a collision with a corridor.
		 *
		 * This method checks if the entity's position will result in a collision with a corridor on the game map.
		 * That means if the entity will collide with a space, that is adjacent to the wall of a corridor.
		 *
		 * @param map The game map.
		 * @param position The position of the entity.
		 * @return True if there is a collision with a corridor, false otherwise.
		 */
		bool corridorCollision(std::vector<std::vector<char>> map, std::pair<size_t, size_t> position) const;

		/**
		 * @brief Formats the tile character.
		 *
		 * This method formats the tile character by changing it to a specific character
		 * based on the entity's interaction with the tile.
		 *
		 * @param tile The tile character to be formated.
		 */
		void formatTile(char& tile) const;

	protected:
		//		y		x
		pair<size_t, size_t> m_Position, m_InitialPosition;
		std::chrono::milliseconds m_Speed;						/**< The speed of the entity's movement in milliseconds (higher value == slower speed). */
    	std::chrono::steady_clock::time_point m_CurrentTime;    /**< The current time for timing the entity's movement. */
    	std::chrono::steady_clock::time_point m_PreviousTime;	/**< The previous time for timing the entity's movement. */
		char m_Direction, m_Character;							/**< The character representation of the entity. */
    	int m_EntityLook;                                       /**< The entity's look for coloring. */
		friend class CGame;		
};