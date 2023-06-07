#include "CEntity.hpp"
#include "CPlayer.hpp"
#include <thread>
#pragma once

class CGhost_1 : public CEntity {
	public:
        CGhost_1();

		virtual ~CGhost_1() = default;

		virtual bool checkCollisions(CMap &, char);

		virtual void move(CMap &, const CPlayer &);

		void mvUp(CMap&);

		void mvDown(CMap&);

		void mvLeft(CMap&);

		void mvRight(CMap&);

		void decideMoveDirection(CMap&, const CPlayer &);


    	void findShortestPath(CMap& , const CPlayer&);


	protected:
		friend class CGame;
};