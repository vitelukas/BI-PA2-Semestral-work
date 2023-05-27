#include <iostream>
#include <string>
#include <ncurses.h>
#include <fstream>
#include <vector>
#include "CLeaderBoard.hpp"
#include "CGameMode.hpp"
#include "CGame.hpp"

#pragma once

class CMainMenu {
	public:
        CMainMenu();
		
		/* Will also show "initial dialog info" */
        void run();

        void prnt();

		void update();

		void startGame();
	
		void end();

	protected:	
		int m_CursorPos, m_MenuItemStart, m_MenuItemEnd, m_xOffset;
		size_t m_Height, m_Width;
		CLeaderBoard m_LeaderBoard;
		CGameMode m_GameMode;
		CGame m_Game;
};