#include "CEntity.hpp"
#pragma once

class CPlayer : public CEntity{
	public:
        CPlayer();

		virtual ~CPlayer() = default;

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
		char m_PrevDirection;
		unsigned int m_Lifes;
		unsigned int m_Score;
		char m_Character;
    	std::chrono::milliseconds m_ElapsedTime;
		friend class CGame;
		friend class CGhost_1;
		friend class CGhost_2;
		friend class CGhost_3;
};