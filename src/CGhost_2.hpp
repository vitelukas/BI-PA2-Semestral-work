#include "CEntity.hpp"
#pragma once

class CGhost_2 : public CEntity{
	public:
        CGhost_2();

		virtual ~CGhost_2() = default;

		virtual void move(CMap &) override;

		virtual bool checkCollisions(CMap &) override;
	
	protected:
};