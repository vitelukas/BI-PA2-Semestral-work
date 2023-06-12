#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <ncurses.h>
#include <climits>
#include <stdexcept>

#pragma once

using namespace std;

/**
 * @class CMap
 * @brief Represents the game map for the game.
 *
 * The CMap class is responsible for loading and managing the game map.
 * It provides methods to load the map from a file, transform tiles on the map,
 * and print the map on the screen using ncurses library.
 */
class CMap {
	public:
		/**
		 * @brief Default constructor for CMap.
		 *
		 * Initializes the CMap object with default values and sets up color pairs for ncurses.
		 */
		CMap();

		/**
		 * @brief Loads the map from a file.
		 * @param fileName The name of the file containing the map data.
		 *
		 * This method reads the map data from a file and populates the internal m_CharMap vector representing the game map.
		 * It also sets the height and width of the map based on the loaded data.
		 *
		 * @throw runtime_error If the map file cannot be opened.
		 */
		void loadMap(const std::string& fileName);

		/**
		 * @brief Transforms a tile on the map.
		 * @param tile The character representing the tile to transform.
		 * @param y The y-coordinate of the tile on the map.
		 * @param x The x-coordinate of the tile on the map.
		 *
		 * This method changes the character at the specified coordinates on the map,
		 * to the given tile assigned to it in the m_AsciiToSymbolMap class attribute.
		 * If the tile is not found in the m_AsciiToSymbolMap, it is used as is.
		 */
		void transformMap(char tile, size_t y, size_t x);

		/**
		 * @brief Prints the map on the screen.
		 *
		 * This method prints the map on the screen using ncurses library.
		 * It applies color pairs based on the characters in the map to represent different tiles.
		 * The map is printed within the screen boundaries.
		 */
		void printMap() const;

	private:
		/**
		 * @brief Check if the loaded map if valid or not.
		 * @return Returns true if the map is ok and valid, false otherwise.
		 */
		bool checkMapValidity();
	
	private:
		size_t m_Height, m_Width;
		char m_CoinCharr;
		std::vector<std::vector<char>> m_CharMap;   ///< The 2D vector representing the map.
		std::unordered_map<char, char> m_AsciiToSymbolMap;  ///< Mapping between ASCII characters and symbols on the map.
		std::pair<size_t, size_t> m_TeleportIn;     ///< The coordinates of the teleport entrance.
		std::pair<size_t, size_t> m_TeleportOut;    ///< The coordinates of the teleport exit.
		friend class CGame;
		friend class CEntity;
		friend class CPlayer;
		friend class CGhost;
		friend class CGhost_1;
		friend class CGhost_2;
};