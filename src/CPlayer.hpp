#include "CEntity.hpp"

#pragma once

class CPlayer : public CEntity {
	public:
		/**
		 * Default constructor.
		 */
		CPlayer();

		/**
		 * Virtual destructor.
		 */
		virtual ~CPlayer() = default;

		/**
		 * Move the player entity on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		void move(CMap& map);

		/**
		 * Override method to decide the movement direction of the player entity.
		 *
		 * @param map Reference to the game map object.
		 * @param entity Reference to the entity object for collision detection.
		 */
		virtual void decideMoveDirection(CMap& map, const CEntity& entity) override;

		/**
		 * Override method to move the player entity upwards on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		virtual void mvUp(CMap& map) override;

		/**
		 * Override method to move the player entity downwards on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		virtual void mvDown(CMap& map) override;

		/**
		 * Override method to move the player entity to the left on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		virtual void mvLeft(CMap& map) override;

		/**
		 * Override method to move the player entity to the right on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		virtual void mvRight(CMap& map) override;

		/**
		 * Override method to check for collisions between the player entity and the game map - walls, corridors, teleports, cherries, coins.
		 *
		 * @param map Reference to the game map object.
		 * @param position Pair representing the position which will be checked collisions.
		 * @return True if a collision occurs, False otherwise.
		 */
		virtual bool checkIfCollisions(CMap& map, pair<size_t, size_t> position) override;

		/**
		 * Collect a coin/cherry from the game map at the specified position and increase the player's score.
		 *
		 * @param map Reference to the game map object.
		 * @param position Pair representing the position of the coin to collect.
		 */
		void collectCoin(CMap& map, pair<size_t, size_t> position);

	protected:
		char m_PrevDirection;
		bool m_IsBerserk;
		unsigned int m_Lives, m_Score;
    	std::chrono::milliseconds m_BerserkDuration;
		friend class CGame;
		friend class CGhost;
		friend class CGhost_1;
		friend class CGhost_2;
		friend class CGhost_3;
		friend class CMainMenu;
};