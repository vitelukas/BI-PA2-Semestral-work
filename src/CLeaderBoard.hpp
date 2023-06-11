#include <string>
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>

#pragma once

/**
 * @class CLeaderBoard
 * @brief Represents a leaderboard for a game.
 * 
 * This class allows displaying the leaderboard and making entries into the leaderboard.
 */
class CLeaderBoard {
	public:
		/**
		 * @brief Constructs a new CLeaderBoard object.
		 */
		CLeaderBoard();

		/**
		 * @brief Displays the leaderboard.
		 * 
		 * @throw runtime_error If the leaderboard file cannot be opened.
		 */
		void showLeaderboard() const;

		/**
		 * @brief Makes an entry in the leaderboard.
		 * @param playerScore The score of the player to be entered.
		 * 
		 * @throw runtime_error If the leaderboard file cannot be opened.
		 */
		void makeEntry(int playerScore) const;

		/**
		 * @brief Retrieves the name of the player from the input.
		 * @return The name of the player.
		 */
		std::string getPlayerName() const;
	
	private:
	
};