#include "CGhost_2.hpp"
using namespace std;

CGhost_2::CGhost_2() {
	m_Position = {20 ,20};
}

void CGhost_2::move(CMap &) {
	return;
}

bool CGhost_2::checkCollisions(CMap &gameMap) {
	return false;
}