#include "CEntity.hpp"

#pragma once

class CPlayer : public CEntity {
	public:
		/**
		 * @brief Default constructor.
		 */
		CPlayer();

		/**
		 * @brief Virtual destructor.
		 */
		virtual ~CPlayer() = default;

		/**
		 * @brief Return the player's score.
		 * @return The value of the player's score.
		 * 
		 */
		unsigned int getScore() const;

		/**
		 * @brief Return the players berserk state.
		 * @return The true if the player is in the berserk state, otherwise return false.
		 * 
		 */
		bool getBerserk() const;


	private:

		/**
		 * @brief Move the player entity on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		void move(CMap& map);

		/**
		 * @brief Override method to decide the movement direction of the player entity.
		 *
		 * @param map Reference to the game map object.
		 * @param entity Reference to the entity object which will be considered for move decision.
		 */
		virtual void decideMoveDirection(CMap& map, const CEntity& entity) override;

		/**
		 * @brief Override method to move the player entity upwards on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		virtual void mvUp(CMap& map) override;

		/**
		 * @brief Override method to move the player entity downwards on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		virtual void mvDown(CMap& map) override;

		/**
		 * @brief Override method to move the player entity to the left on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		virtual void mvLeft(CMap& map) override;

		/**
		 * @brief Override method to move the player entity to the right on the game map.
		 *
		 * @param map Reference to the game map object.
		 */
		virtual void mvRight(CMap& map) override;

		/**
		 * @brief Override method to check for collisions between the player entity and the game map - walls, corridors, teleports, cherries, coins.
		 *
		 * @param map Reference to the game map object.
		 * @param position Pair representing the position which will be checked for collisions.
		 * @return True if a collision occurs, False otherwise.
		 */
		virtual bool checkIfCollisions(CMap& map, pair<size_t, size_t> position) override;

		/**
		 * @brief Collect a coin/cherry from the game map at the specified position and increase the player's score.
		 *
		 * @param map Reference to the game map object.
		 * @param position Pair representing the position of the coin to collect.
		 */
		void collectCoin(CMap& map, pair<size_t, size_t> position);

	private:
		char m_PrevDirection;
		bool m_IsBerserk;
        unsigned int m_Lives, m_Score, m_FinalScore;
        std::chrono::milliseconds m_BerserkDuration;
		friend class CGame;
};