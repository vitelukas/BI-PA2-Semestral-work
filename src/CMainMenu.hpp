#include "CGame.hpp"
#include "CLeaderBoard.hpp"
#include <fstream>
#include <ncurses.h>
#include <sstream>
#include <string>

#pragma once

/**
 * @class CMainMenu
 * @brief Represents the main menu of a game.
 *
 * The CMainMenu class provides functionality for displaying and managing the main menu of a game. It allows the player to choose various options such as starting a new game, choosing difficulty, viewing the leaderboard, and exiting the game.
 */
class CMainMenu {
public:
    /**
     * @brief Default constructor.
     */
    CMainMenu();

    /**
     * @brief Destructor.
     */
    ~CMainMenu() = default;

    /**
     * @brief The most important method of the class. Runs the main menu.
     * @param gameMode The game mode to be passed to the game.
     * @return An integer indicating the next action to be taken( num != 0 -> run the main menu again, otherwise end the whole program ).
     *
     * This method runs the main menu until the player chooses to start the game or exit. It handles user input and updates the cursor position accordingly. It also allows the player to choose the difficulty and view the leaderboard.
     */
    int run(int gameMode);

private:
    /**
     * @brief Prints the main menu items to the screen.
     */
    void prnt() const;

    /**
     * @brief Updates the display and the current cursor position, thus highlighting the current menu item.
     */
    void update() const;

    /**
     * @brief General function to print all the initial menu items and texts of the main menu.
     */
    void initialPrint() const;

    /**
     * @brief Prints a banner at the top of the main menu.
     */
    void printBanner() const;

    /**
     * @brief Prompts the player to choose a difficulty level.
     */
    void chooseDifficulty();

    /**
     * @brief Loads the game configuration from a config file and sets up the game modes attribues accordingly.
     * @param fileName The name of the configuration file.
     *
     * This method reads the game configuration from a file and sets the attributes of different game modes (Easy, Medium, Hard) accordingly.
     *
     * @throw runtime_error If the config file cannot be opened.
     */
    void loadConfig(const std::string &fileName);

    /**
     * @brief Loads the variable values from a config file into the input string stream parameter.
     * @param configFile The name of the configuration file.
     * @param iss Reference to an input string stream for storing the variable values.
     * @param numOfLines Reference to a variable representing the number of lines in the config file.
     *
     * This method reads the game configuration from a file and loads the attribute values of different game modes into the iss variable,
     * which is then used for parsing the variable values into the variables in the calling function.
     */
    void getAttributes(ifstream &configFile, istringstream &iss, int &numOfLines);

    /**
     * @brief Check the validity of the loaded attributes;
     * @param iss Reference to the input string stream for storing the variable values.
     * @param lives The number of lives for the player.
     * @param entitySpeed The speed of the entities in the game.
     * @param ghostSlower The speed of the ghosts in the game.
     * @param berserkDuration The duration of the berserker mode in the game.
     *
     * This method checks if the attributes have to correct format and if all the attributes were loaded.
     * The function throws an exception if something fails.
     */
    void checkAttrs(istringstream &iss, const int &lives, const int &entitySpeed, const int &ghostSlower, const int &berserkDuration);

    /**
     * @brief Check if the loading of the map file was successful.
     * @param iss Reference to the input string with the map.
     */
    void checkMapFile(const istringstream &iss);

    /**
     * @brief Determines the final game mode(which will be then passed to the game, as an object), based on the currently set game mode.
     */
    void decideFinalGameMode();

private:
    int m_MenuItemStart,    /// Position of the first menu item
        m_MenuItemEnd,      /// 	 -||-	    last    -||-
        m_CursorPos,        /// Current cursor position in the menu
        m_xOffset,          /// The position for the start of pritning a text
        m_ChooseDifficulty, /// The position of the choice for choosing a difficulty
        m_ShowLeaderboard;  /// 			    -||-		   showing the leaderboard
    size_t m_Height, m_Width;
    CGame m_Game;
    CGameMode m_PlayEasy, m_PlayMedium, m_PlayHard, m_FinalGameMode;
    CLeaderBoard m_LeaderBoard;
};