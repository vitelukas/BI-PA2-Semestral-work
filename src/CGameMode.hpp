#pragma once

class CGameMode {
	public:

		CGameMode();

		void setAttributes(int, int, int, int);
		
		int m_EntitySpeed, m_GhostSpeed;
		int m_PlayerLives;
		int m_BerserkerDuration;
	protected:

};
		