#include <fstream>
#include <sstream>
#include <string>
#include <ncurses.h>
#include "CLeaderBoard.hpp"
#include "CGame.hpp"

#pragma once

class CMainMenu {
	public:
        CMainMenu();

		~CMainMenu() = default;
		
        int run(int gameMode);

        void prnt() const;

		void update() const;

		void chooseDifficulty();

		void loadConfig(const std::string&);

		void decideFinalGameMode();

		void initialPrint() const;

		void printBanner() const;

	protected:	
		int m_MenuItemStart,		// Position of the first menu item
			m_MenuItemEnd,			// 		-||-	   last	   -||-
			m_CursorPos,			// Current cursor position in the menu
			m_xOffset,				// The position for the start of pritning a text
			m_ChooseDifficulty,		// The position of the choice for choosing a difficulty
			m_ShowLeaderboard;		// 			    -||-			  showing the leaderboard
		size_t m_Height, m_Width;
		CGame m_Game;
		CGameMode m_PlayEasy, m_PlayMedium, m_PlayHard, m_FinalGameMode;
		CLeaderBoard m_LeaderBoard;
};