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

		bool checkCollisions(CMap &) override;
		
		void collectCoin(CMap &);

		void undoCollision(int , int, CMap &);

		void decideMoveDirection(CMap &);
	
	protected:
		char m_Direction, m_PrevDirection;
		unsigned int m_Lifes;
		unsigned int m_Score;
		char m_Character;
		friend class CGame;

    	std::chrono::milliseconds m_ElapsedTime;
    	std::chrono::steady_clock::time_point m_PreviousTime;
};