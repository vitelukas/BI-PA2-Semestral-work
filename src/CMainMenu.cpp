#include "CMainMenu.hpp"
using namespace std;

CMainMenu::CMainMenu() {
    clear();
    m_CursorPos = 10;
    m_MenuItemStart = 10;
    m_ChooseDiffPosition = m_MenuItemStart + 1;
    m_ShowLeaderboard = m_MenuItemStart + 2;
    m_MenuItemEnd = m_MenuItemStart + 3;
	getmaxyx(stdscr, m_Height, m_Width); 
    m_xOffset = (getmaxx(stdscr) / 2) - 3;

    // int height = 20;
    // int width = 20;
    // int start_y = 10;
    // int start_x = 10;
    // WINDOW *menuWin = newwin(height, width, start_y, start_x);
    // refresh();
    // box (menuWin, 0, 0);
    // wrefresh(menuWin);
}

CMainMenu::~CMainMenu() {
    endwin();
}

int CMainMenu::run() {    
    char getInput;
    while(true){
        update();
        
        // move the cursor
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
                m_Game.run();

                m_LeaderBoard.makeEntry(m_Game.m_Player.m_Score);

                return 1;

            } else if ( m_CursorPos == m_ChooseDiffPosition) {
                //todo Choose difficulty
                chooseDifficulty();
            } else if ( m_CursorPos == m_ShowLeaderboard) {
                m_LeaderBoard.showLeaderboard();
            } else if( m_CursorPos == m_MenuItemEnd ) {
                return 0;
            }
        }

    }
}

void:: CMainMenu::update() {
    clear();
    int y = m_MenuItemStart;
    int x = m_xOffset;

    int offset = m_CursorPos - m_MenuItemStart;
    mvprintw(y + offset, x, ">> ");

    prnt();
    return;
}

void:: CMainMenu::prnt() {
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

void CMainMenu::chooseDifficulty() {
    return;
}