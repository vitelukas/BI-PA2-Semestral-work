#include "CGhost.hpp"
#pragma once

class CGhost_2 : public CGhost {
	public:
		CGhost_2();
		
		virtual void decideMoveDirection(CMap&, const CPlayer &) override;

	protected:
};