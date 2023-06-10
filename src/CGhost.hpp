#include "CEntity.hpp"
#include "CPlayer.hpp"
#include <ctime>

#pragma once

class CGhost : public CEntity {
	public:
		CGhost();

		virtual void move(CMap &, const CPlayer &);

		virtual void decideMoveDirection(CMap&, const CEntity &) override;

		virtual void mvUp(CMap&)  override;

		virtual void mvDown(CMap&) override;

		virtual void mvLeft(CMap&) override;

		virtual void mvRight(CMap&) override;

		virtual bool checkIfCollisions(CMap &, pair<size_t, size_t>) override;

		bool checkDirectionOK(char) const;

		char determineDirection(pair<size_t, size_t>) const;

		void chooseRandomMove(CMap&);

	protected:
		unordered_map<char, int> m_BackDirections;
		unordered_map<int, char> m_DirectionsTable;
		int m_GhostSlower;
		friend class CGame;
};