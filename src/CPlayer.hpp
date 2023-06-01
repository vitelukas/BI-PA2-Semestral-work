#include "CEntity.hpp"
#pragma once

class CPlayer : public CEntity{
	public:
        CPlayer();

		virtual void move(CMap &) override;

		void mvUp(CMap &);

		void mvDown(CMap &);

		void mvLeft(CMap &);

		void mvRight(CMap &);

		bool checkCollisions(CMap &);
		
		void collectCoin(CMap &);
	
	protected:
		unsigned int m_Lifes;
		unsigned int m_Score;
		char m_Character;
		friend class CGame;
};