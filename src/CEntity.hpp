#include <algorithm>
#include "CMap.hpp"
#pragma once

class CEntity {
	public:
        CEntity()
			: m_Position(0,0)
		{}

		virtual ~CEntity() {}

		virtual void move(CMap &) = 0;
	
	protected:
		pair<int, int> m_Position;
		friend class CGame;
};