#include "CMainMenu.hpp"
using namespace std;

#define CONFIG_FILE "./examples/config/game_config.txt"

CMainMenu::CMainMenu() 
    : m_MenuItemStart(12), m_CursorPos(m_MenuItemStart)
{
    clear();
    m_ChooseDifficulty = m_MenuItemStart + 1;
    m_ShowLeaderboard = m_MenuItemStart + 2;
    m_MenuItemEnd = m_MenuItemStart + 3;
	getmaxyx(stdscr, m_Height, m_Width); 
    m_xOffset = (getmaxx(stdscr) / 2) - 9;
}

int CMainMenu::run(int gameMode) {
    loadConfig(CONFIG_FILE);
    m_Game.m_GameMode = gameMode;
    char getInput;
    
    initialPrint();

    // Run the main menu until the player chooses to play the game or end the program
    while(true){
        update();
        
        getInput = tolower(getch());
        // Clear the previous choice
        mvprintw(m_CursorPos, m_xOffset, "   ");

        if( getInput == 'w' ) {
            m_CursorPos--;
        }
        else if( getInput == 's') {
            m_CursorPos++;
        }

        if (m_CursorPos < m_MenuItemStart) {
			m_CursorPos = m_MenuItemEnd;
		}
        else if (m_CursorPos > m_MenuItemEnd ) {
			m_CursorPos = m_MenuItemStart;
		}

        // Choose what action should be performed based on the cursor position
        if (getInput == '\n') {
            if ( m_CursorPos == m_MenuItemStart ) {
                decideFinalGameMode();

                m_Game.run(m_FinalGameMode);

                // Allow the user to sign the leaderboard after he finishes the game
                m_LeaderBoard.makeEntry(m_Game.m_Player.m_Score);

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
                return 0;
            }
        }
    }
}

void:: CMainMenu::update() const {
    int y = m_CursorPos;
    int x = m_xOffset;

    mvprintw(y, x, ">> ");

    refresh();

    return;
}

void:: CMainMenu::prnt() const {
    int y = m_MenuItemStart;
    int x = m_xOffset + 3;

    mvprintw(y++, x, "new game\n");
    mvprintw(y++, x, "choose difficulty\n");
    mvprintw(y++, x, "show leaderboard\n");
    mvprintw(y++, x, "end\n");

    move(m_Height - 8, 0);
    printw("Controls:\nUp -> w\nDown -> s\nLeft -> a\nRight -> d\n\nPress enter to confirm your choice");

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

void CMainMenu::loadConfig(const string &fileName) {
    ifstream configFile(fileName);
    string line;
    int lives, entitySpeed, ghostSlower, berserkDuration;

    if ( !configFile.is_open() ) {
		cerr << "Error while opening the config file!" << endl;
		throw runtime_error("Failed to open the config file.");
	}

    while (getline(configFile, line)) {
        // Skip empty lines or lines starting with '#' == comment line
        if (line.empty() || line[0] == '#')
            continue;

        // Parse the line into variables
        istringstream iss(line);

        // Store the values in appropriate object attributes
        if (line.find("Easy") != string::npos) {          // Handle Easy game mode 
            getline(configFile, line);
            iss.str(line);
            iss >> lives >> entitySpeed >> ghostSlower >> berserkDuration;
            m_PlayEasy.setAttributes(lives, entitySpeed, ghostSlower, berserkDuration);
        } 
        else if (line.find("Medium") != string::npos) {   // Handle Medium game mode
            getline(configFile, line);
            iss.str(line);
            iss >> lives >> entitySpeed >> ghostSlower >> berserkDuration;
            m_PlayMedium.setAttributes(lives, entitySpeed, ghostSlower, berserkDuration);
        } 
        else if (line.find("Hard") != string::npos) {     // Handle Hard game mode
            getline(configFile, line);
            iss.str(line);
            iss >> lives >> entitySpeed >> ghostSlower >> berserkDuration;
            m_PlayHard.setAttributes(lives, entitySpeed, ghostSlower, berserkDuration);
        }
    }

    configFile.close();

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

void CMainMenu::printBanner() const {
    if (m_Height <= 14)
        return;
    int start = 1;
    int x = m_Width/2 - 35;
    mvprintw(start++, x, " ______   ______     ______           __    __     ______     __   __\n");
    mvprintw(start++, x, "/\\  == \\ /\\  __ \\   /\\  ___\\         /\\ \"-./  \\   /\\  __ \\   /\\ \"-.\\ \\\n");
    mvprintw(start++, x, "\\ \\  _-/ \\ \\  __ \\  \\ \\ \\____  _____ \\ \\ \\-./\\ \\  \\ \\  __ \\  \\ \\ \\-.  \\\n");
    mvprintw(start++, x, " \\ \\_\\    \\ \\_\\ \\_\\  \\ \\_____\\ \\____\\ \\ \\_\\ \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\\\\"\\_\\\n");
    mvprintw(start++, x, "  \\/_/     \\/_/\\/_/   \\/_____/         \\/_/  \\/_/   \\/_/\\/_/   \\/_/ \\/_/\n");
}