#include "CGhost.hpp"

#pragma once

class CGhost_3 : public CGhost {
	public:
		CGhost_3();

		virtual void decideMoveDirection(CMap&, const CPlayer &) override;

		virtual void mvUp(CMap&) override;

		virtual void mvDown(CMap&) override;

		virtual void mvLeft(CMap&) override;

		virtual void mvRight(CMap&) override;

		void chooseRandomMove(CMap&);

	protected:
		friend class CGame;
};