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

	protected:	
		int m_CursorPos, m_MenuItemStart, m_MenuItemEnd, m_xOffset, m_ChooseDifficulty, m_ShowLeaderboard;
		size_t m_Height, m_Width;
		CGame m_Game;
		CGameMode m_PlayEasy, m_PlayMedium, m_PlayHard, m_FinalGameMode;
		CLeaderBoard m_LeaderBoard;
};