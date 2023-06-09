#include "CGhost.hpp"

#pragma once

class CGhost_3 : public CGhost {
	public:
		CGhost_3();

		virtual void decideMoveDirection(CMap&, const CEntity &) override;

	protected:
		friend class CGame;
};