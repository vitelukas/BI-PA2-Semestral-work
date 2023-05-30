#include "CGame.hpp"
using namespace std;

void CGame::run() {
    m_Map.loadMap("examples/main_map.txt");
    m_Map.showMap();

    while(true) {
        reloadMap();
    }

    return;
}

void CGame::update() {
    return;
}

void CGame::reloadMap() {
    return;
}