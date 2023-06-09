#include "CGhost.hpp"
#include <queue>

#pragma once

class CGhost_1 : public CGhost {
	public:
		CGhost_1();

		virtual void decideMoveDirection(CMap&, const CEntity &) override;

    	void findShortestPath(CMap& , const CEntity &, size_t &, size_t &);

	protected:
		friend class CGame;
};