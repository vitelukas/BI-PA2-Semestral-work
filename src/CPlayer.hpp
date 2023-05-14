#include "CEntity.hpp"

class CPlayer : public CEntity{
	public:
        CPlayer();
		~CPlayer();

	
	protected:
		unsigned int m_Lifes;
		unsigned int m_Score;
};