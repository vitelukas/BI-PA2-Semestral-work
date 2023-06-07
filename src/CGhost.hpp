#include "CEntity.hpp"
#include "CPlayer.hpp"
#include <thread>
#include <ctime>
#pragma once

class CGhost : public CEntity {
	public:
		CGhost();

		virtual void move(CMap &, const CPlayer &);

		virtual void decideMoveDirection(CMap&, const CPlayer &) = 0;

		virtual void mvUp(CMap&)  override;

		virtual void mvDown(CMap&) override;

		virtual void mvLeft(CMap&) override;

		virtual void mvRight(CMap&) override;

		virtual bool checkIfCollisions(CMap &, char);

		virtual bool checkIfCollisions(CMap&, char, pair<size_t, size_t>);

		bool checkDirectionOK(char);

		void formatTile(char&);

		char determineDirection(pair<size_t, size_t>);

	protected:
		unordered_map<int, char> m_BackDirections;
		unordered_map<int, char> m_DirectionsTable;
		int m_GhostSlower;
};