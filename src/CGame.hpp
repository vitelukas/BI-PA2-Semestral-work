#include "CMap.hpp"
#include "CGameMode.hpp"
#include "CEntity.hpp"
#include "CPlayer.hpp"
#include "CGhost_1.hpp"
#include "CGhost_2.hpp"
#include "CGhost_3.hpp"
#include <stdio.h>
#include <iostream>

#pragma once


/**
 * @class CGame
 * @brief Represents the game(actual playing) and its functionalities.
 * 
 * It manages the game state, entities, and gameplay mechanics.
 */
class CGame {
	public:
		/**
		 * @brief Constructs a new CGame object with default values.
		 */
		CGame();

		/**
		 * @brief Runs the game with the specified game mode.
		 * @param gameMode The game mode to be set and played.
		 */
		void run(const CGameMode &gameMode);

	protected:
		/**
		 * @brief Initializes the game with the specified game mode.
		 * @param gameMode The game mode to be initialized/set.
		 */
		void initializeGame(const CGameMode &gameMode);

		/**
		 * @brief Updates the game state.
		 * @param berserkActive Flag indicating if berserk mode is active.
		 * 
		 * Update includes showing the current game stats, collision update, berserk mode update, etc.
		 */
		void updateGameState(int berserkActive);

		/**
		 * @brief Handles the collision between the player and ghosts.
		 */
		void handleGhostCollision();

		/**
		 * @brief Handles the collision between the player and ghosts during berserk mode.
		 */
		void handleBerserkCollision();

		/**
		 * @brief Checks if there is a collision between the player and ghosts.
		 * @return The ID of the ghost involved in the collision, or 0 if no collision.
		 */
		int checkGhostCollision();

		/**
		 * @brief Sets the entity to the initial state after a collision.
		 * @param whichEntity The ID of the entity to set after collision, or -1 for all entities.
		 */
		void setEntityAfterCollision(int whichEntity = -1);

		/**
		 * @brief Reloads the game map.
		 */
		void reloadMap() const;

		/**
		 * @brief Sets the entities on the game map based on the given entity symbol and position.
		 * @param entity The symbol representing the entity.
		 * @param y The y-coordinate of the entity position.
		 * @param x The x-coordinate of the entity position.
		 */
		void setEntities(char entity, size_t y, size_t x);

		/**
		 * @brief Starts the berserk mode for the player and the ghosts.
		 */
		void goBerserk();

		/**
		 * @brief Displays the message for winning the game.
		 */
		void playerWon() const;

		/**
		 * @brief Displays the message for losing the game.
		 */
		void playerLost() const;

		/**
		 * @brief Sets the game configuration based on the provided game mode.
		 * @param gameMode The game mode with the desired configuration.
		 */
		void setGameConfig(const CGameMode &gameMode);

	protected:
		int m_GameMode;
		bool m_GameIsDone;
		unsigned int m_ScoreToWin, m_EatenGhosts;
		CMap m_Map;	
		CPlayer m_Player;
		CGhost_1 m_Ghost_1;
		CGhost_2 m_Ghost_2;
		CGhost_3 m_Ghost_3;
		friend class CMainMenu;
};