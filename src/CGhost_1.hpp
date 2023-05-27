#include "CEntity.hpp"
#pragma once

class CGhost_1 : public CEntity{
	public:
        CGhost_1();

		virtual void move() override;

	protected:
};