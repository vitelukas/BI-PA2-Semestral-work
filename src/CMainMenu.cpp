#include "CMainMenu.hpp"
using namespace std;

#define CONFIG_FILE "./examples/config/game_config.txt"

CMainMenu::CMainMenu() {
    clear();
	getmaxyx(stdscr, m_Height, m_Width);
    m_MenuItemStart = m_Height >= 20 ? 12 : 2;
    m_CursorPos = m_MenuItemStart;
    m_ChooseDifficulty = m_MenuItemStart + 1;
    m_ShowLeaderboard = m_MenuItemStart + 2;
    m_MenuItemEnd = m_MenuItemStart + 3;
    m_xOffset = max((getmaxx(stdscr) / 2) - 9, 0);
}

int CMainMenu::run(int gameMode) {
    // Load the variable values from the config file
    loadConfig(CONFIG_FILE);
    // Set the previous game mode
    m_Game.m_GameMode = gameMode;
    char getInput;
    // -1 == wait until there is an input from user
    timeout(-1);
    
    initialPrint();

    // Run the main menu until the player chooses to play the game or end the program
    while(true){
        update();
        
        // Wait for the user input
        getInput = tolower(getch());
        // Clear the previous choice
        mvprintw(m_CursorPos, m_xOffset, "   ");

        if( getInput == 'w' ) {
            m_CursorPos--;
        }
        else if( getInput == 's') {
            m_CursorPos++;
        }
        
        // Switch the cursor position to the last, respectively first position,
        // if the cursor position underflows / overflows the menu item list
        if (m_CursorPos < m_MenuItemStart) {
			m_CursorPos = m_MenuItemEnd;
		}
        else if (m_CursorPos > m_MenuItemEnd ) {
			m_CursorPos = m_MenuItemStart;
		}

        // Choose what action should be performed based on the current cursor position
        if (getInput == '\n') {
            if ( m_CursorPos == m_MenuItemStart ) {
                decideFinalGameMode();

                m_Game.run(m_FinalGameMode);

                // Allow the user to sign the leaderboard after he finishes the game
                m_LeaderBoard.makeEntry(m_Game.m_Player.getScore());

                // return value 1 == start main menu again 
                return m_Game.m_GameMode;
            } 
            else if ( m_CursorPos == m_ChooseDifficulty) {
                chooseDifficulty();
                initialPrint();
            } 
            else if ( m_CursorPos == m_ShowLeaderboard) {
                m_LeaderBoard.showLeaderboard();
                initialPrint();
            } 
            else if( m_CursorPos == m_MenuItemEnd ) {
                // Return 0 == dont't run the main menu again
                return 0;
            }
        }
    }
    clear();
}

// Update the currently highlighted menu item (based on the current cursor position)
void CMainMenu::update() const {
    int y = m_CursorPos;
    int x = m_xOffset;

    mvprintw(y, x, ">> ");

    refresh();

    return;
}

void CMainMenu::prnt() const {
    int y = m_MenuItemStart;
    int x = m_xOffset + 3;

    mvprintw(y++, x, "new game\n");
    mvprintw(y++, x, "choose difficulty\n");
    mvprintw(y++, x, "show leaderboard\n");
    mvprintw(y++, x, "end\n");

    y = m_Height >= 8 ? m_Height - 9 : 0;
    x = 0;
    move(y, x);
    mvprintw(y++, x, "Controls:");
    mvprintw(y++, x, "Up -> w");
    mvprintw(y++, x, "Down -> s");
    mvprintw(y++, x, "Left -> a");
    mvprintw(y++, x, "Right -> d");
    mvprintw(y+1, x, "\nPress enter to confirm your choice");
}

void CMainMenu::chooseDifficulty() {
    clear();
    int positionEasy = m_Height/2 - 4;
    int positionMedium = m_Height/2 - 2;
    int positionHard = m_Height/2;

    int choice = positionEasy;

    attron(A_STANDOUT);
    mvprintw(positionEasy -4, m_Width/2 - 8, "CHOOSE DIFFICULTY");
    attroff(A_STANDOUT);

    mvprintw(positionEasy, m_Width/2 - 2, "EASY");
    mvprintw(positionMedium, m_Width/2 - 3, "MEDIUM");
    mvprintw(positionHard, m_Width/2 - 2, "HARD");

    // Stay in the choose difficulty menu, until the user chooses a difficulty
    while(true){
        mvprintw(choice, m_Width/2 - 6, ">> ");
        refresh();
        
        char getInput = tolower(getch());
        mvprintw(choice, m_Width/2 - 6, "   ");

        if( getInput == 'w' ) {
            choice -= 2;
        }
        else if( getInput == 's') {
            choice += 2;
        }

        // Switch the choice(cursor position) to the last, respectively first position,
        // if the cursor position underflows / overflows the menu item list
        if (choice < positionEasy) {
			choice = positionHard;
		}
        else if (choice > positionHard ) {
			choice = positionEasy;
		}

        // Choose what action should be performed based on the cursor position
        if (getInput == '\n') {
            if ( choice == positionEasy) {
                m_Game.m_GameMode = 1;
            } 
            else if ( choice == positionMedium) {
                m_Game.m_GameMode = 2;
            } 
            else if( choice == positionHard ) {
                m_Game.m_GameMode = 3;
            }
            break;
        }
    }
        
    return;
}

void CMainMenu::decideFinalGameMode() {
    switch (m_Game.m_GameMode) {
        case 1:
            m_FinalGameMode = m_PlayEasy;
            break;
        case 2:
            m_FinalGameMode = m_PlayMedium;
            break;
        case 3:
            m_FinalGameMode = m_PlayHard;
            break;
        default:
            break;
    }
}

void CMainMenu::initialPrint() const {
    clear();
    prnt();
    printBanner();
}

void CMainMenu::loadConfig(const string &fileName) {
    ifstream configFile(fileName);
    string line;
    string mapFile;
    int lives, entitySpeed, ghostSlower, berserkDuration;
    int numOfLines = 0;
    bool mapFlag, easyFlag, mediumFlag, hardFlag;
    mapFlag = easyFlag = mediumFlag = hardFlag = false;

    if ( !configFile.is_open() ) {
		cerr << "Error while opening the config file!" << endl;
		throw runtime_error("Failed to open the config file.");
	}

    // Read the confif file while there are lines to be processed
    while (getline(configFile, line)) {
        // Skip empty lines or lines starting with '#' == comment line
        if (line.empty() || line[0] == '#')
            continue;

        // Parse the line into variables
        istringstream iss(line);

        // Store the values in appropriate object attributes
        if (line.find("Map") != string::npos) {          // Handle Easy game mode 
            getAttributes(configFile, iss, numOfLines);
            iss >> mapFile;
            m_Game.m_MapFile = mapFile;
            m_PlayEasy.setAttributes(lives, entitySpeed, ghostSlower, berserkDuration);
            mapFlag = true;
        }
        else if (line.find("Easy") != string::npos) {          // Handle Easy game mode 
            getAttributes(configFile, iss, numOfLines);
            iss >> lives >> entitySpeed >> ghostSlower >> berserkDuration;
            checkAttrs(iss, lives, entitySpeed, ghostSlower, berserkDuration);
            m_PlayEasy.setAttributes(lives, entitySpeed, ghostSlower, berserkDuration);
            easyFlag = true;
        } 
        else if (line.find("Medium") != string::npos) {   // Handle Medium game mode
            getAttributes(configFile, iss, numOfLines);
            iss >> lives >> entitySpeed >> ghostSlower >> berserkDuration;
            checkAttrs(iss, lives, entitySpeed, ghostSlower, berserkDuration);
            m_PlayMedium.setAttributes(lives, entitySpeed, ghostSlower, berserkDuration);
            mediumFlag = true;
        } 
        else if (line.find("Hard") != string::npos) {     // Handle Hard game mode
            getAttributes(configFile, iss, numOfLines);
            iss >> lives >> entitySpeed >> ghostSlower >> berserkDuration;
            checkAttrs(iss, lives, entitySpeed, ghostSlower, berserkDuration);
            m_PlayHard.setAttributes(lives, entitySpeed, ghostSlower, berserkDuration);
            hardFlag = true;
        }
        numOfLines++;

        // If the config file is too long, stop loading
        if (numOfLines >= 500)
            break;
    }

    configFile.close();

    if ( !(mapFlag && easyFlag && mediumFlag && hardFlag) ) {
        cerr << "Error while loading the config file!" << endl;
		throw runtime_error("The config file doesn't have the right structure: at least one game mode specification is missing!");
    }

    return;
}

void CMainMenu::checkAttrs(istringstream &iss, const int &lives, const int &entitySpeed, const int &ghostSlower, const int &berserkDuration) {
    // Check if the loading failed - if it failed the format of the values was incorrect or atleast one of the values was missing
    if ( iss.fail() ) {
        cerr << "Error while loading attribute values!" << endl;
		throw runtime_error("Error while loading attribute values: not all values were specified, or the values are not numbers!");
    }

    if ( lives < 0 || entitySpeed < 0 || ghostSlower < 0 || berserkDuration < 0 ) {
        cerr << "Error while loading attribute values!" << endl;
		throw runtime_error("Error while loading attribute values: the attribute values cannot have negative value!");
    }

    int dummy;
    if (iss >> dummy) {
        cerr << "Error while loading attribute values!" << endl;
        throw runtime_error("Error while loading attribute values: too many attributes!");
    }  

}

void CMainMenu::getAttributes(ifstream &configFile, istringstream &iss, int &numOfLines) {
    string line;
    while (getline(configFile, line)) {
        if (!line.empty() && line[0] != '#' && !isspace(line[0])) {
            iss.str(line);
            break;
        }
        numOfLines++;

        if (numOfLines >= 500)
            break;
    }
}

void CMainMenu::printBanner() const {
    if (m_Height <= 20)
        return;
    
    int start = 1;
    int x = m_Width/2 - 35;
    mvprintw(start++, x, " ______   ______     ______           __    __     ______     __   __\n");
    mvprintw(start++, x, "/\\  == \\ /\\  __ \\   /\\  ___\\         /\\ \"-./  \\   /\\  __ \\   /\\ \"-.\\ \\\n");
    mvprintw(start++, x, "\\ \\  _-/ \\ \\  __ \\  \\ \\ \\____  _____ \\ \\ \\-./\\ \\  \\ \\  __ \\  \\ \\ \\-.  \\\n");
    mvprintw(start++, x, " \\ \\_\\    \\ \\_\\ \\_\\  \\ \\_____\\ \\____\\ \\ \\_\\ \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\\\\"\\_\\\n");
    mvprintw(start++, x, "  \\/_/     \\/_/\\/_/   \\/_____/         \\/_/  \\/_/   \\/_/\\/_/   \\/_/ \\/_/\n");
}