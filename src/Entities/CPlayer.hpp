#include "CEntity.hpp"
#pragma once

class CPlayer : public CEntity{
	public:
        CPlayer()
			: m_Lifes(3), m_Score(0) 
		{}

		virtual void move() override;
	
	protected:
		unsigned int m_Lifes;
		unsigned int m_Score;
};