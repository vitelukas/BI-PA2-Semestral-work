#include "CMap.hpp"
#include <algorithm>
#include <chrono>
#pragma once

class CEntity {
	public:
        CEntity();

		virtual ~CEntity() {}

		virtual void decideMoveDirection(CMap&, const CEntity &) = 0;

		virtual void mvUp(CMap&) = 0;

		virtual void mvDown(CMap&) = 0;

		virtual void mvLeft(CMap&) = 0;

		virtual void mvRight(CMap&) = 0;
		
		virtual bool checkIfCollisions(CMap &, pair<size_t, size_t>);

		bool wallCollision(const CMap &, pair<size_t, size_t>) const;

		bool corridorCollision(vector<vector<char>>, pair<size_t, size_t>) const;

		void formatTile(char&) const;

		std::pair<size_t, size_t> getPosition() const;

		char getDirection() const;

	protected:
		//		y		x
		pair<size_t, size_t> m_Position, m_InitialPosition;
		std::chrono::milliseconds m_Speed;
    	std::chrono::steady_clock::time_point m_CurrentTime, m_PreviousTime;
		char m_Direction, m_Character; 
		int m_EntityLook;
		friend class CGame;		
};