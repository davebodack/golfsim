#include "golfsim.h"
#include "Player.h"
#include "utilities.cpp"
#include "calculations.cpp"
#include "career.cpp"
#include "matchplay.cpp"
#include "oneonone.cpp"
#include "international.cpp"
#include "draft.cpp"
#include "players2020.cpp"


//The main function prompts the user to choose the mode of simulation they would like to execute,
//and executes each form of simulation based on what the user selects
int main(int argc, char* argv[]) {

	cout << "\nWelcome! This is the Historical Golf Legend Simulator.\n\n";
	ifstream infile;
	bool playersflag = false;

	if (argc > 1) {
		infile.open(argv[1]);
		if (strcmp(argv[1], "players2020.txt") == 0) {
			playersflag = true;
		}
	}

	else {
		while (!infile.is_open()) {
			string filename;
			cout << "Error! No valid filename entered. Please input the name of a valid file containing data on the golfers you would like to use: \n";
			cin >> filename;
			infile.open(filename.c_str());
		}
	}

	if (playersflag == true) {

		cout << "Welcome to the simulation of the cancelled 2020 Players Championship. :(\nThis simulation will resume from the end of Round 1 of The Players and show what may have happened by the end of Round 4.\nHow many tournaments would you like to simulate?\n";
		int numtourneys;
		cin >> numtourneys;
		while ((!cin) || (numtourneys < 1)) {
			cout << "Invalid nuber of tournaments entered. Please enter the number of 2020 Players Championships you'd like to simulate:\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cin >> numtourneys;
		}

		//143 players, minus Louis Oosthuizen who withdrew, were eligible to continue playing in the 2020 Players
		int golfernum = 143;
		Player golfers[golfernum];	

		for (int i = 0; i < golfernum; i++) {
		
			string name = "";
			while (name.find(":") == string::npos) {
				string nameinput = "";
				infile >> nameinput;
				name.append(nameinput);
				name.append(" ");
			}

			golfers[i].name = name.substr(0, name.length() - 2);
			infile >> golfers[i].rating;
			infile >> golfers[i].score;
			//Allows resetting scores back to what they were in real life after Rd. 1 of 2020 Players
			golfers[i].originalscore = golfers[i].score;
		}

		players_2020(golfers, golfernum, numtourneys);

	} else {

		string input;
		cout << "If you'd like to simulate a full career, type 'Career'. \nIf you'd like to simulate a match play tournament, type 'Match Play'. \nIf you'd like to pit two golfers against each other, type 'One on One'. \nIf you'd like to simulate an all-time Ryder Cup or Presidents Cup, type 'International'.\nIf you'd like to draft two teams of players and pit them against each other, type 'Draft'.\n\n"; 
		getline(cin, input);

		while ((input != "Career") && (input != "career") && (input != "match play") && (input != "Match play") && (input != "Match Play") && (input != "one on one") && (input != "1 on 1") && (input != "One on One") && (input != "One On One") && (input != "Ryder Cup") && (input != "International") && (input != "international") && (input != "intl") && (input != "Draft") && (input != "draft")) {
			cout << "Oops! You entered an invalid input. Try again: to simulate a full career, type 'career'. To simulate match play, type 'match play'. To pit two golfers against each other in a one on one match, type 'one on one'. If you'd like to simulate an all-time Ryder Cup, type 'Ryder Cup'.\n";
			getline(cin, input);
		}

		int golfernum = 100;
		Player golfers[golfernum];			
		int counter = 0;

		//Reads in the names and ratings from the file into the players
		for (int i = 0; i < golfernum; i++) {
			
			string name = "";
			while (name.find(":") == string::npos) {
				string nameinput = "";
				infile >> nameinput;
				name.append(nameinput);
				name.append(" ");
			}

			golfers[i].name = name.substr(0, name.length() - 2);
			infile >> golfers[i].rating;
			infile >> golfers[i].nationality;
		}

		if ((input == "Career") || (input == "career")) {
			career(golfers, golfernum);
		}

		else if ((input == "Match Play") || (input == "Match play") || (input == "match play")) {
			matchplay(golfers);
		}

		else if ((input == "one on one") || (input == "1 on 1") || (input == "One on One") || (input == "One On One")) {
			oneonone(golfers, golfernum);	
		}	

		else if ((input == "International") || (input == "international") || (input == "intl")) {
			international(golfers, golfernum);
		}

		else if ((input == "Draft") || (input == "draft")) {
			draft(golfers, golfernum);
		}
	}

	infile.close();
}

