#include "CMap.hpp"
#include <algorithm>
#include <chrono>
#pragma once

class CEntity {
	public:
        CEntity();

		virtual ~CEntity() {}

		void decideMoveDirection(CMap &);

		virtual void mvUp(CMap&) = 0;

		virtual void mvDown(CMap&) = 0;

		virtual void mvLeft(CMap&) = 0;

		virtual void mvRight(CMap&) = 0;
		
		virtual bool checkIfCollisions(CMap &, pair<size_t, size_t>);

		bool wallCollision(const CMap &, pair<size_t, size_t>);

		bool corridorCollision(vector<vector<char>>, pair<size_t, size_t>);

	protected:
		//		y		x
		pair<size_t, size_t> m_Position;
		std::chrono::milliseconds m_Speed;
    	std::chrono::steady_clock::time_point m_PreviousTime;
		char m_Direction, m_Character; 
		int m_EntityLook;
		friend class CGame;
};
