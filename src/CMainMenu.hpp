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

	protected:	
		int m_CursorPos, m_MenuItemStart, m_MenuItemEnd, m_xOffset, m_ChooseDiffPosition, m_ShowLeaderboard;
		size_t m_Height, m_Width;
		CGame m_Game;
		CGameMode m_GameMode;
		CLeaderBoard m_LeaderBoard;
};