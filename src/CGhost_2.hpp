#include "CGhost.hpp"
#include <queue>

#pragma once

class CGhost_2 : public CGhost {
	public:
		CGhost_2();

		virtual void decideMoveDirection(CMap&, const CEntity &) override;

    	void findShortestPath(CMap& , const CEntity &, size_t &, size_t &);

	protected:
		friend class CGame;
};