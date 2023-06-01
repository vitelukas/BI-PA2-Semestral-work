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

		~CMainMenu();
		
		/* Will also show "initial dialog info" */
        int run();

        void prnt();

		void update();

		void chooseDifficulty();
		
		void signLeaderBoard();

		void end();

	protected:	
		int m_CursorPos, m_MenuItemStart, m_MenuItemEnd, m_xOffset, m_ChooseDiffPosition;
		size_t m_Height, m_Width;
		CLeaderBoard m_LeaderBoard;
		CGameMode m_GameMode;
		CGame m_Game;
};