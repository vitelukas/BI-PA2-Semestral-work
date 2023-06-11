#include "CLeaderBoard.hpp"
using namespace std;

#define LEADERBOARD_FILE "examples/leaderboard/leaderboard.txt"

CLeaderBoard::CLeaderBoard() {}

void CLeaderBoard::makeEntry(int playerScore) const {
    string playerName = getPlayerName();
    ifstream inputFile(LEADERBOARD_FILE);

    if (!inputFile.is_open()) {
        cerr << "Error while opening the leaderboard file!" << endl;
        throw runtime_error("Failed to open the leaderboard file.");
    }

    // Read existing entries and store them in a vector
    vector<pair<string, int>> leaderboardEntries;
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name;
        int score;
		string dummy;
        ss >> dummy >> name >> score;
		name.pop_back(); // remove the ":"
        leaderboardEntries.emplace_back(name, score);
    }
    inputFile.close();

    // Insert the new entry in the correct position
    leaderboardEntries.emplace_back(playerName, playerScore);
    sort(leaderboardEntries.begin(), leaderboardEntries.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Sort in descending order based on score
    });
	
    // Rewrite the leaderboard file with the updated entries
    ofstream outputFile(LEADERBOARD_FILE); // Open the file in write mode
	int position = 1;
    for (const auto& entry : leaderboardEntries) {
        outputFile << position << ". " << entry.first << ": " << entry.second << endl;
		position++;
    }

    outputFile.close(); // Close the file
}

string CLeaderBoard::getPlayerName() const {
    clear();
	timeout(-1);

    char ch = 'n';
    string playerName;
    size_t x, y, xOffset;
	xOffset = (getmaxx(stdscr)/2) - 10;
    x = xOffset + 7;
    y = 6;

    attron(A_UNDERLINE | A_STANDOUT);
    mvprintw(4, xOffset, "PLEASE ENTER YOUR NAME");
    attroff(A_UNDERLINE | A_STANDOUT);

	move(y, x);
	curs_set(1);

    flushinp(); // Clear the input buffer

    while (true) {
        ch = getch();

        if (ch == '\n') {
            if (!playerName.empty()) {
                break;                  // Break the loop if the user entered a non-empty name
            }
        } 
        else if (ch == KEY_BACKSPACE || ch == 127) {
            if (!playerName.empty()) {
                playerName.pop_back();  // Remove the last character if backspace was pressed and the name is not empty
            }
        } 
        else if ( !isspace(ch) && (isalnum(ch) || isspace(ch) || ch == '_') ) {
            playerName.push_back(ch);   // Append alphanumeric characters and spaces to the player's name
        }
        else {
            mvprintw(y + 10, x - 17, "Only alnum chars and underscore(_) are allowed.");
        }


        move(y, 0);
        clrtoeol();                     // Clear the whole line before printing the name again
        move(y, 0);

        mvprintw(y, x, "%s", playerName.c_str());
        refresh();
    }

	curs_set(0);

    return playerName;
}


void CLeaderBoard::showLeaderboard() const {
	clear();

	ifstream sourceFile(LEADERBOARD_FILE);

    if ( !sourceFile.is_open() ) {
		cerr << "Error while opening the leaderboard file!" << endl;
		throw runtime_error("Failed to open the leaderboard file.");
	}
	
	string line;
	size_t x, y, maxY;
	y = 3;
	x = (getmaxx(stdscr) / 2) - 3;
	maxY = getmaxy(stdscr);
	attron(A_UNDERLINE | A_STANDOUT);
	mvprintw(1, x, "LEADERBOARD");
	attroff(A_UNDERLINE | A_STANDOUT);

	mvprintw(maxY - 2, 1, "Press any key to exit.");

	while (getline(sourceFile, line)) {
		mvprintw(y, x, "%s", line.c_str());
		y++;
	}

	sourceFile.close();

	refresh();
	getch();
}