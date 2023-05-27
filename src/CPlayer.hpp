#include "CEntity.hpp"
#pragma once

class CPlayer : public CEntity{
	public:
        CPlayer();

		virtual void move() override;
	
	protected:
		unsigned int m_Lifes;
		unsigned int m_Score;
};