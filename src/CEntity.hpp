#pragma once
#include <algorithm>

class CEntity {
	public:
        CEntity()
			: m_Position(0,0)
		{}

		virtual void move() = 0;
	
	protected:
	std::pair<int, int> m_Position;
};