#include "CEntity.hpp"

#pragma once

class CPlayer : public CEntity{
	public:
        CPlayer();

		virtual ~CPlayer() = default;

		void move(CMap &);

		virtual void decideMoveDirection(CMap &);

		void mvUp(CMap &) override;

		void mvDown(CMap &) override;

		void mvLeft(CMap &) override;

		void mvRight(CMap &) override;

		virtual bool checkIfCollisions(CMap &);
		
		void collectCoin(CMap &);

		void undoCollision(int , int, CMap &);

	protected:
		char m_PrevDirection;
		bool m_IsBerserk;
		unsigned int m_Lifes, m_Score;
    	std::chrono::milliseconds m_BerserkTime;
		friend class CGame;
		friend class CGhost;
		friend class CGhost_1;
		friend class CGhost_2;
		friend class CGhost_3;
		friend class CMainMenu;
};