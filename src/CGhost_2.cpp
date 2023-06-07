#include "CGhost_2.hpp"
using namespace std;

CGhost_2::CGhost_2() 
	: CGhost() 
{
    m_Character = '@';
    m_EntityLook = 6;
}

void CGhost_2::decideMoveDirection(CMap& gameMap, const CPlayer & player) {
	return;
}
