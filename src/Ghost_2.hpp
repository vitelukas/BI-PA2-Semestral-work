#include "CGhost.hpp"
#include <queue>
#pragma once

class CGhost_2 : public CGhost {
	public:
		CGhost_2();

		virtual void decideMoveDirection(CMap&, const CPlayer &) override;

    	void findShortestPath(CMap& , const CPlayer&, size_t &, size_t &);

	protected:
		friend class CGame;
};
