#include <stdio.h>
#include <iostream>
#include "CMap.hpp"
#include "CPlayer.hpp"
#include "CGhost_1.hpp"
#include "CGhost_2.hpp"
#include "CGhost_3.hpp"

#pragma once


class CGame {
	public:
		CGame();

		void run();

		void update();

		void reloadMap();

		void setEntities(char entity, int x, int y);

	protected:
		bool m_GameIsDone;
		size_t m_ScoreToWin;
		CMap m_Map;	
		CPlayer m_Player;
		CGhost_1 m_Ghost_1;
		CGhost_2 m_Ghost_2;
		CGhost_3 m_Ghost_3;
};