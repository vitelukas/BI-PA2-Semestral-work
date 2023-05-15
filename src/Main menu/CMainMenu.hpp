#include <iostream>
#include <string>
#include <ncurses.h>
#include "CLeaderBoard.hpp"
#include "CGameMode.hpp"
#include "CGame.hpp"

#pragma once

class CMainMenu {
	public:
        CMainMenu()
			: m_CursorPos(0), m_Height(0), m_Width(0)  
		{}
		
		/* Will also show "initial dialog info " */
        void run();

        void prnt();

		void update();

		void startGame();
	
		void end();

	protected:	
		int m_CursorPos;
		size_t m_Height;
		size_t m_Width;
		CLeaderBoard m_LeaderBoard;
		CGameMode m_GameMode;
		CGame m_Game;

};