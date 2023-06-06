#include "CMap.hpp"
#include <algorithm>
#include <chrono>
#pragma once

class CEntity {
	public:
        CEntity();

		virtual ~CEntity() {}
		
		virtual void move(CMap &);

		virtual bool checkCollisions(CMap &);

		bool wallCollision(CMap);

		bool corridorCollision(vector<vector<char>>);

		bool checkDirectionOK(char);

		void formatTile(char&);

	protected:
		//		y		x
		pair<size_t, size_t> m_Position;
		std::chrono::milliseconds m_Speed;
    	std::chrono::steady_clock::time_point m_PreviousTime;
		unordered_map<char, char> m_backDirections;
		char m_Direction;
		friend class CGame;
};