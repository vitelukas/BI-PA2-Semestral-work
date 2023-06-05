#include "CMap.hpp"
#include <algorithm>
#include <chrono>
#pragma once

class CEntity {
	public:
        CEntity()
			: m_Position(0,0)
		{}

		virtual ~CEntity() {}

		virtual void move(CMap &) = 0;

		virtual bool checkCollisions(CMap &);

		virtual bool wallCollision(CMap);

		virtual bool corridorCollision(vector<vector<char>>);
	
	protected:
		//		y		x
		pair<size_t, size_t> m_Position;
		std::chrono::milliseconds m_Speed;
		friend class CGame;
};