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
		void run();

		void update();

		bool reloadMap(m_Map); 

	protected:
		CMap m_Map;	
		CPlayer m_Player;
		CGhost_1 m_Ghost_1;
		CGhost_2 m_Ghost_2;
		CGhost_3 m_Ghost_3;
};