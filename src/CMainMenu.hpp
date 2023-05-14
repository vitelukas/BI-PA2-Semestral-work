#include <iostream>
#include <string>
#include <ncurses.h>
#include "CLeaderBoard.hpp"

class CMainMenu {
	public:
        CMainMenu();
		~CMainMenu();

		void startGame();

		void end();

		void update();
    
        void run();
        
        void prnt();
	
	protected:	
		int cursPos;
		CLeaderBoard leaderBoard;
};