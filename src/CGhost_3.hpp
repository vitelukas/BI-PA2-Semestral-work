#include "CEntity.hpp"
#include "CPlayer.hpp"
#include <thread>
#include <ctime>
#pragma once

class CGhost_3 : public CEntity {
	public:
        CGhost_3();

		virtual ~CGhost_3() = default;

		virtual void move(CMap &, const CPlayer &);

		void mvUp(CMap&);

		void mvDown(CMap&);

		void mvLeft(CMap&);

		void mvRight(CMap&);

		void decideMoveDirection(CMap&, const CPlayer &);

		void chooseRandomMove(CMap&);

		virtual bool checkCollisions(CMap &, char);

	protected:
		friend class CGame;
};