#include "CGhost_3.hpp"
using namespace std;

CGhost_3::CGhost_3() {
	m_Position = {30 ,30};
}

void CGhost_3::move(CMap &) {
	return;
}

bool CGhost_3::checkCollisions(CMap &gameMap) {
	return false;
}