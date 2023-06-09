#include "CEntity.hpp"

#pragma once

class CPlayer : public CEntity{
	public:
        CPlayer();

		virtual ~CPlayer() = default;

		void move(CMap &);

		virtual void decideMoveDirection(CMap&, const CEntity &) override;

		virtual void mvUp(CMap &) override;

		virtual void mvDown(CMap &) override;

		virtual void mvLeft(CMap &) override;

		virtual void mvRight(CMap &) override;

		virtual bool checkIfCollisions(CMap &, pair<size_t, size_t>) override;
		
		void collectCoin(CMap &);

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