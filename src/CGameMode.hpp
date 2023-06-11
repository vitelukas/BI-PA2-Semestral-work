#pragma once

/**
 * @class CGameMode
 * @brief Represents the game's game mode and its attributes.
 * 
 * It allows setting and retrieving the attributes of the game mode.
 */
class CGameMode {
	public:
		/**
		 * @brief Constructs a new CGameMode object with default attribute's values.
		 */
		CGameMode();

		/**
		 * @brief Sets the attributes of the game mode.
		 * @param lives The number of lives for the player.
		 * @param entitySpeed The speed of the entities in the game.
		 * @param ghostSlower The speed of the ghosts in the game.
		 * @param berserkDuration The duration of the berserker mode in the game.
		 */
		void setAttributes(int lives, int entitySpeed, int ghostSlower, int berserkDuration);

		// Attributes of the game mode
		int m_EntitySpeed;       // Speed of the entities
		int m_GhostSpeed;        // Speed of the ghosts
		int m_PlayerLives;       // Number of lives for the player
		int m_BerserkerDuration; // Duration of the berserker mode
	protected:
};
