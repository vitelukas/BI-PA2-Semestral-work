#include "CMainMenu.hpp"
using namespace std;

#define CONFIG_FILE "./examples/config/game_config.txt"

CMainMenu::CMainMenu() 
    : m_CursorPos(10), m_MenuItemStart(10)
{
    clear();
    m_ChooseDifficulty = m_MenuItemStart + 1;
    m_ShowLeaderboard = m_MenuItemStart + 2;
    m_MenuItemEnd = m_MenuItemStart + 3;
	getmaxyx(stdscr, m_Height, m_Width); 
    m_xOffset = (getmaxx(stdscr) / 2) - 3;
}

int CMainMenu::run(int gameMode) {
    loadConfig(CONFIG_FILE);
    m_Game.m_GameMode = gameMode;
    char getInput;

    // Run the main menu until the player chooses to play the game or end the program
    while(true){
        update();
        
        // move the cursor to the start of the menu
        move(m_MenuItemStart, m_xOffset);

        getInput = tolower(getch());

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
                //TODO Choose difficulty
                chooseDifficulty();
            } 
            else if ( m_CursorPos == m_ShowLeaderboard) {
                m_LeaderBoard.showLeaderboard();
            } 
            else if( m_CursorPos == m_MenuItemEnd ) {
                return 0;
            }
        }
    }
}

void:: CMainMenu::update() const {
    clear();
    int y = m_MenuItemStart;
    int x = m_xOffset;

    int offset = m_CursorPos - m_MenuItemStart;
    mvprintw(y + offset, x, ">> ");

    prnt();
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
    return;
}

//TODO
void CMainMenu::chooseDifficulty() {
    //set m_Game.m_GameMode

    m_Game.m_GameMode = 3;

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