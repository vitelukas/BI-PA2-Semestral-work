#include "CMap.hpp"
#include "CEntity.hpp"
#include "CPlayer.hpp"
#include "CGhost_1.hpp"
#include "CGhost_2.hpp"
#include "CGhost_3.hpp"
#include <stdio.h>
#include <iostream>

#pragma once


class CGame {
	public:
		CGame();

		void run();

		void initializeGame();

		void updateGameState(int);

		void handleGhostCollision();

		void handleBerserkCollision();

		int checkGhostCollision();

		void setEntityAfterCollision(int = -1);

		void reloadMap();

		void setEntities(char entity, size_t x, size_t y);

		void goBerserk();

		void playerWon();

	protected:
		bool m_GameIsDone;
		size_t m_ScoreToWin;
		CMap m_Map;	
		CPlayer m_Player;
		CGhost_1 m_Ghost_1;
		CGhost_2 m_Ghost_2;
		CGhost_3 m_Ghost_3;
		friend class CMainMenu;
};