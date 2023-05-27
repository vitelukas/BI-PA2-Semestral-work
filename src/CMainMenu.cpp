#include "CMainMenu.hpp"
using namespace std;

CMainMenu::CMainMenu() {
    clear();
    m_CursorPos = 10;
    m_MenuItemStart = 10;
    m_MenuItemEnd = 13;
    m_xOffset = 65;
	m_Width = 100;
	m_Height = 100;

    // int height = 20;
    // int width = 20;
    // int start_y = 10;
    // int start_x = 10;

    // WINDOW *menuWin = newwin(height, width, start_y, start_x);
    // refresh();
    // box (menuWin, 0, 0);
    // wrefresh(menuWin);
}

void CMainMenu::run() {
    update();
    
    char getInput;
    while(true){
        move(m_MenuItemStart, m_xOffset);
        getInput = getch();
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

        if( getInput == '\n' && m_CursorPos == m_MenuItemEnd) {
			end();
            return;
		}
        else if ( getInput == '\n' && m_CursorPos == m_MenuItemStart ) {
			startGame();
		}

        update();
        prnt();
    }
    return;
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
    mvprintw(y++, x, "show leader board\n");
    mvprintw(y++, x, "end\n");

    move(29, 0);
    printw("Controls:\nUp -> w\nDown -> s\nLeft -> a\nRight -> d\n\nPress enter to confirm your choice");
    return;
}

void:: CMainMenu::startGame() {
    return;
}

void:: CMainMenu::end() {
    return;
}