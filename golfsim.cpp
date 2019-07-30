//Author: David Bodack
//Date: 7/2/19

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <math.h>

using namespace std;

class Player {
public:
	std::string name;
	double rating;
	double matchrating;
	char nationality;
	int pgatourwins;
	int majorswon;
	int masterswon;
	int pgaswon;
	int usopenswon;
	int openswon;
	int numtourneyswon;
	int nummatcheswon;

	Player() {
		name = "";
		rating = 0;
		matchrating = 0;
		nationality = '\0';
		pgatourwins = 0;
		majorswon = 0;
		masterswon = 0;
		pgaswon = 0;
		usopenswon = 0;
		openswon = 0;
		numtourneyswon = 0;
		nummatcheswon = 0;
	}
};


double sum(Player golfers[], int golfernum) {
	
	double sum = 0;

	for (int i = 0; i < golfernum; i++) {
		sum += golfers[i].rating;
	}
	return sum;
}


Player determine_winner(Player golfers[], int golfernum, int major) {
	
	double ratingsum = sum(golfers, golfernum);
	ratingsum += 0.5;
	int intsum = (int) ratingsum;
	int randomnum = (rand() % intsum) + 1;
		
	for (int i = 0; i < golfernum; i++) {
		randomnum -= golfers[i].rating;
		if (randomnum <= 0) {
			golfers[i].majorswon++;
			
			if (major == 0) {
				golfers[i].pgatourwins++;
				golfers[i].majorswon--;
			}
			else if (major == 1) {
				golfers[i].masterswon++;
				golfers[i].pgatourwins++;
			}
			else if (major == 2) {
				golfers[i].pgaswon++;
				golfers[i].pgatourwins++;
			}
			else if (major == 3) {
				golfers[i].usopenswon++;
				golfers[i].pgatourwins++;
			}
			else if (major == 4) {
				golfers[i].openswon++;
				golfers[i].pgatourwins++;
			}

			return golfers[i];
		}
	}

	return golfers[0];
}

bool determine_match_winner(Player golfer1, Player golfer2) {
	
	int matchratingsum = (int) (golfer1.matchrating + golfer2.matchrating + 0.5);
	return (rand() % matchratingsum) < golfer1.matchrating;
}

int determine_hole_winner(Player golfer1, Player golfer2) {

	int ratingtotal = (int) ((golfer1.matchrating * 2) + (golfer2.matchrating * 2) + 0.5);
	int oneononerandnum = (rand() % ratingtotal);
	if (oneononerandnum < golfer1.matchrating) {
		return 1;
	} else if (oneononerandnum < (ratingtotal - golfer2.matchrating)) {
		return 2;
	} else {
		return 3;
	}
	return 0;
}

void swap(Player& x, Player& y) {
	
	Player temp;
	temp = x;
	x = y;
	y = temp;
}


void sort(Player golfers[], int golfernum) {
	
	for (int num = 1; num < golfernum; num++) {
		for (int i = 0; i < golfernum - num; i++) {
			if (golfers[i].majorswon < golfers[i+1].majorswon) {
				swap(golfers[i], golfers[i+1]);
			}
			else if ((golfers[i].majorswon == golfers[i+1].majorswon) && (golfers[i].pgatourwins < golfers[i+1].pgatourwins)) {
				swap(golfers[i], golfers[i+1]);
			}
		}
	}
}


void match_sort(Player golfers[], int golfernum) {
	
	for (int num = 1; num < golfernum; num++) {
		for (int i = 0; i < golfernum - num; i++) {
			if (golfers[i].numtourneyswon < golfers[i+1].numtourneyswon) {
				swap(golfers[i], golfers[i+1]);
			}
		}
	}
}


int main(int argc, char* argv[]) {

	cout << "Welcome! This is the Historical Golf Legend Simulator.\n";
	ifstream infile;
	
	if (argc > 1) {
		infile.open(argv[1]);
	}

	else {
		while (!infile.is_open()) {
			string filename;
			cout << "Error! No valid filename entered. Please input the name of a valid file containing data on the golfers you would like to use: \n";
			cin >> filename;
			infile.open(filename.c_str());
		}
	}

	string input;
	cout << "If you'd like to simulate a full career, type 'career'. If you'd like to simulate a match play tournament, type 'match play'. If you'd like to draft a golfer and play a match against someone, type 'one on one'.\n"; 
	getline(cin, input);

	while ((input != "Career") && (input != "career") && (input != "match play") && (input != "Match play") && (input != "Match Play") && (input != "one on one") && (input != "1 on 1") && (input != "One on One") && (input != "One On One")) {
		cout << "Oops! You entered an invalid input. Try again: to simulate a full career, type 'career'. To simulate match play, type 'match play'. To pit two golfers against each other in a one on one match, type 'one on one'.\n";
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
		
		//Randomly shuffles players in the golfers array
		int n = golfernum - 1;
		Player temp;
		int p;

		while(n > 0) {
			srand(time(NULL));
			p = rand() % n+1;
			temp = golfers[n];
			golfers[n] = golfers[p];
			golfers[p] = temp;
			n--;
		}	

		cout << "How many years would you like to simulate? (20 years is recommended to simulate a full career): ";
		int numyears;
		cin >> numyears;

		int numtournaments = 30;

		for (int i = 0; i < numyears; i++) {
			
			Player winner = determine_winner(golfers, golfernum, 1);
			cout << winner.name << " claims the green jacket at the " << i + 2020 << " Masters!" << '\n';
			winner = determine_winner(golfers, golfernum, 2);
			cout << winner.name << " is victorious at the " << i + 2020 << " PGA Championship!" << '\n';
			winner = determine_winner(golfers, golfernum, 3);
			cout << winner.name << " triumphs over golf's ultimate test at the " << i + 2020 << " U.S. Open!" << '\n';
			winner = determine_winner(golfers, golfernum, 4);
			cout << winner.name << " is the Champion Golfer of the Year at the " << i + 2020 << " Open Championship!" << '\n';
			
			for (int i = 0; i < numtournaments - 4; i++) {
				winner = determine_winner(golfers, golfernum, 0);
			}
		}

		sort(golfers, golfernum);
		cout << '\n' << "Here are the results of simulating a career for these golfers of " << numyears << " years: " << '\n' << '\n';

		for (int i = 0; i < golfernum; i++) {
			cout << golfers[i].name << ": " << golfers[i].pgatourwins << " PGA Tour events won, " << golfers[i].majorswon << " majors (" << golfers[i].masterswon << " Masters, " << golfers[i].pgaswon << " PGA Championships, " << golfers[i].usopenswon << " U.S. Opens, " << golfers[i].openswon << " Open Championships)" << '\n';
		}
		
		infile.close();
	}

	else if ((input == "Match Play") || (input == "Match play") || (input == "match play")) {

		//Fix once golfernum isn't hard-coded in
		int matchgolfernum = 64;
		Player matchgolfersrd1[matchgolfernum];
		Player matchgolfersrd2[matchgolfernum / 2];
		Player matchgolfersrd3[matchgolfernum / 4];
		Player matchgolfersrd4[matchgolfernum / 8];
		Player matchgolfersrd5[matchgolfernum / 16];
		Player matchgolfersrd6[matchgolfernum / 32];

		for (int i = 0; i < matchgolfernum; i++) {
			matchgolfersrd1[i] = golfers[i];
		}

		srand(time(NULL));
		bool result;
		int numtourneys;
		cout << "How many tournaments would you like to simulate?" << '\n';
		cin >> numtourneys;

		double ratingavg;
		Player golfer1;
		Player golfer2;

		for (int i = 0; i < numtourneys; i++) {
			for (int i = 0; i < matchgolfernum; i += 2) {
				
				golfer1 = matchgolfersrd1[i];
				golfer2 = matchgolfersrd1[matchgolfernum - (i+1)];
				ratingavg = (golfer1.rating + golfer2.rating) / 2;
				golfer1.matchrating = (golfer1.rating + ratingavg) / 2;
				golfer2.matchrating = (golfer2.rating + ratingavg) / 2;
				matchgolfersrd1[i] = golfer1;
				matchgolfersrd1[matchgolfernum - (i+1)] = golfer2;

				result = determine_match_winner(matchgolfersrd1[i], matchgolfersrd1[matchgolfernum - (i+1)]);
				if (result == true) {
					if (numtourneys < 2) {
						cout << matchgolfersrd1[i].name << " defeats " << matchgolfersrd1[matchgolfernum - (i+1)].name << " in Round 1 of the Legends Match Play Championship." << '\n';
					}
					matchgolfersrd2[i/2] = matchgolfersrd1[i];
				}
				else {
					if (numtourneys < 2) {
						cout << matchgolfersrd1[matchgolfernum - (i+1)].name << " defeats " << matchgolfersrd1[i].name << " in Round 1 of the Legends Match Play Championship." << '\n';
					}
					matchgolfersrd2[i/2] = matchgolfersrd1[matchgolfernum - (i+1)];
				}
			}

			if (numtourneys < 2) {
				cout << '\n';
			}

			for (int i = 0; i < matchgolfernum / 2; i += 2) {
				
				golfer1 = matchgolfersrd2[i];
				golfer2 = matchgolfersrd2[(matchgolfernum / 2) - (i+1)];
				ratingavg = (golfer1.rating + golfer2.rating) / 2;
				golfer1.matchrating = (golfer1.rating + ratingavg) / 2;
				golfer2.matchrating = (golfer2.rating + ratingavg) / 2;
				matchgolfersrd2[i] = golfer1;
				matchgolfersrd2[(matchgolfernum / 2) - (i+1)] = golfer2;

				result = determine_match_winner(matchgolfersrd2[i], matchgolfersrd2[(matchgolfernum / 2) - (i+1)]);
				if (result == true) {
					if (numtourneys < 2) {
						cout << matchgolfersrd2[i].name << " defeats " << matchgolfersrd2[(matchgolfernum / 2) - (i+1)].name << " in Round 2." << '\n';
					}
					matchgolfersrd3[i/2] = matchgolfersrd2[i];
				}
				else {
					if (numtourneys < 2) {
						cout << matchgolfersrd2[(matchgolfernum / 2) - (i+1)].name << " defeats " << matchgolfersrd2[i].name << " in Round 2." << '\n';
					}
					matchgolfersrd3[i/2] = matchgolfersrd2[(matchgolfernum / 2) - (i+1)];
				}
			}
			
			if (numtourneys < 2) {
				cout << '\n';
			}

			for (int i = 0; i < matchgolfernum / 4; i += 2) {
				
				golfer1 = matchgolfersrd3[i];
				golfer2 = matchgolfersrd3[(matchgolfernum / 4) - (i+1)];
				ratingavg = (golfer1.rating + golfer2.rating) / 2;
				golfer1.matchrating = (golfer1.rating + ratingavg) / 2;
				golfer2.matchrating = (golfer2.rating + ratingavg) / 2;
				matchgolfersrd3[i] = golfer1;
				matchgolfersrd3[(matchgolfernum / 4) - (i+1)] = golfer2;

				result = determine_match_winner(matchgolfersrd3[i], matchgolfersrd3[(matchgolfernum / 4) - (i+1)]);
				if (result == true) {
					if (numtourneys < 2) {
						cout << matchgolfersrd3[i].name << " defeats " << matchgolfersrd3[(matchgolfernum / 4) - (i+1)].name << " in Round 3." << '\n';
					}
					matchgolfersrd4[i/2] = matchgolfersrd3[i];
				}
				else {
					if (numtourneys < 2) {
						cout << matchgolfersrd3[(matchgolfernum / 4) - (i+1)].name << " defeats " << matchgolfersrd3[i].name << " in Round 3." << '\n';
					}
					matchgolfersrd4[i/2] = matchgolfersrd3[(matchgolfernum / 4) - (i+1)];
				}
			}

			if (numtourneys < 2) {
				cout << '\n';
			}

			for (int i = 0; i < matchgolfernum / 8; i += 2) {
				
				golfer1 = matchgolfersrd4[i];
				golfer2 = matchgolfersrd4[(matchgolfernum / 8) - (i+1)];
				ratingavg = (golfer1.rating + golfer2.rating) / 2;
				golfer1.matchrating = (golfer1.rating + ratingavg) / 2;
				golfer2.matchrating = (golfer2.rating + ratingavg) / 2;
				matchgolfersrd4[i] = golfer1;
				matchgolfersrd4[(matchgolfernum / 8) - (i+1)] = golfer2;

				result = determine_match_winner(matchgolfersrd4[i], matchgolfersrd4[(matchgolfernum / 8) - (i+1)]);
				if (result == true) {
					if (numtourneys < 2) {
						cout << matchgolfersrd4[i].name << " defeats " << matchgolfersrd4[(matchgolfernum / 8) - (i+1)].name << " in the quarterfinals!" << '\n';
					}
					matchgolfersrd5[i/2] = matchgolfersrd4[i];
				}
				else {
					if (numtourneys < 2) {
						cout << matchgolfersrd4[(matchgolfernum / 8) - (i+1)].name << " defeats " << matchgolfersrd4[i].name << " in the quarterfinals!" << '\n';
					}
					matchgolfersrd5[i/2] = matchgolfersrd4[(matchgolfernum / 8) - (i+1)];
				}
			}

			if (numtourneys < 2) {
				cout << '\n';
			}

			for (int i = 0; i < matchgolfernum / 16; i += 2) {
				
				golfer1 = matchgolfersrd5[i];
				golfer2 = matchgolfersrd5[(matchgolfernum / 16) - (i+1)];
				ratingavg = (golfer1.rating + golfer2.rating) / 2;
				golfer1.matchrating = (golfer1.rating + ratingavg) / 2;
				golfer2.matchrating = (golfer2.rating + ratingavg) / 2;
				matchgolfersrd5[i] = golfer1;
				matchgolfersrd5[(matchgolfernum / 16) - (i+1)] = golfer2;

				result = determine_match_winner(matchgolfersrd5[i], matchgolfersrd5[(matchgolfernum / 16) - (i +1)]);
				if (result == true) {
					if (numtourneys < 2) {
						cout << matchgolfersrd5[i].name << " defeats " << matchgolfersrd5[(matchgolfernum / 16) - (i+1)].name << " in the semifinals to advance to the championship round!" << '\n';
					}
					matchgolfersrd6[i/2] = matchgolfersrd5[i];
				}
				else {
					if (numtourneys < 2) {
						cout << matchgolfersrd5[(matchgolfernum / 16) - (i+1)].name << " defeats " << matchgolfersrd5[i].name << " in the seminfinals to advance to the championship round!" << '\n';
					}
					matchgolfersrd6[i/2] = matchgolfersrd5[(matchgolfernum / 16) - (i+1)];
				}
			}

			if (numtourneys < 2) {
				cout << '\n';
			}
			
			ratingavg = (matchgolfersrd6[0].rating + matchgolfersrd6[1].rating) / 2;
			matchgolfersrd6[0].matchrating = (matchgolfersrd6[0].rating + ratingavg) / 2;
			matchgolfersrd6[1].matchrating = (matchgolfersrd6[1].rating + ratingavg) / 2;

			result = determine_match_winner(matchgolfersrd6[0], matchgolfersrd6[1]);
			if (result == true) {
				cout << matchgolfersrd6[0].name << " defeats " << matchgolfersrd6[1].name << " in the final round to emerge victorious at the Legends Match Play Championship!" << '\n' << '\n';
				for (int i = 0; i < matchgolfernum; i++) {
					if (matchgolfersrd1[i].name == matchgolfersrd6[0].name) {
						matchgolfersrd1[i].numtourneyswon++;
					}
				}
			}
			else {
				cout << matchgolfersrd6[1].name << " defeats " << matchgolfersrd6[0].name << " in the final round to emerge victorious at the Legends Match Play Championship!" << '\n' << '\n';
				for (int i = 0; i < matchgolfernum; i++) {
					if (matchgolfersrd1[i].name == matchgolfersrd6[1].name) {
						matchgolfersrd1[i].numtourneyswon++;
					}
				}
			}
		}

		match_sort(matchgolfersrd1, matchgolfernum);
		if (numtourneys > 1) {
			for (int i = 0; i < matchgolfernum; i++) {
				cout << matchgolfersrd1[i].name << ": " << matchgolfersrd1[i].numtourneyswon << " match play tournaments won" << '\n';
			}
		}
	}

	else if ((input == "one on one") || (input != "1 on 1") || (input != "One on One") || (input != "One On One")) {
		
		Player player1;
		Player player2;
		string playername;

		for (int i = 1; i < 3; i++) {
			bool foundplayer = false;
			while (foundplayer == false) {
				cout << "Player " << i << ": Choose your golfer by typing in their name here: ";
				getline(cin, playername);
				for (int j = 0; j < golfernum; j++) {
					if ((playername == golfers[j].name) && (playername != player1.name)) {
						if (i == 1) {
							player1 = golfers[j];
							foundplayer = true;
						}
						else {
							player2 = golfers[j];
							foundplayer = true;
						}

						srand(time(NULL));
						int randomresponse = rand() % 3;
						if (randomresponse == 0) {
							cout << "Good choice, Player " << i << "!\n";
						}
						else if (randomresponse == 1) {
							cout << "Hmm... interesting choice, Player " << i << ".\n";
						}
						else {
							cout << "Let's hope you don't regret that choice, Player " << i << ".\n";
						}
					}
				}

				if ((foundplayer == false) && (playername == player1.name)) {
					cout << "You can't choose the same golfer as Player 1!\n";
				}

				else if (foundplayer == false) {
					cout << "Invalid player name entered.\n";
				}
			}	
		}

		int nummatches;
		cout << "How many matches between these two would you like to simulate? \n";
		cin >> nummatches;

		while ((!cin) || (nummatches < 1)) {
			cout << "Invalid number of matches entered. Please enter a valid number of matches to be simulated:\n";
			cin >> nummatches;
		}

		double ratingavg = (player1.rating + player2.rating) / 2;
		player1.matchrating = (player1.rating + ratingavg) / 2;
		player2.matchrating = (player2.rating + ratingavg) / 2;

		cout << "Rating average: " << ratingavg << '\n';
		cout << player1.name << " match rating: " << player1.matchrating << '\n';
		cout << player2.name << " match rating: " << player2.matchrating << '\n';

		for (int i = 0; i < nummatches; i++) {
			bool victoryflag = false;
			int roundsum = 0;
			int numholesleft = 18;
			int holeresult = 0;
			for (int i = 1; i < 19; i++) {
				if ((abs(roundsum) > numholesleft) && (victoryflag == false)) {
					if (roundsum < 0) {
						victoryflag = true;
						player1.nummatcheswon++;
						if (nummatches == 1) {
							cout << player1.name << " defeats " << player2.name << " " << abs(roundsum) << " & " << numholesleft << "!\n";
						}		
					}
					else {
						victoryflag = true;
						player2.nummatcheswon++;
						if (nummatches == 1) {
							cout << player2.name << " defeats " << player1.name << " " << abs(roundsum) << " & " << numholesleft << "!\n";
						}	
					}
				}

				else {
					holeresult = determine_hole_winner(player1, player2);
					numholesleft--;
					if (holeresult == 1) {
						roundsum--;
					}
					if (holeresult == 3) {
						roundsum++;
					}
				}
			}

			if ((roundsum == 0) && (nummatches == 1)) {
				cout << player1.name << " and " << player2.name << " tie the match.\n";
			}
		}

		if (nummatches > 1) {
			cout << "\nNumber of matches: " << nummatches << "\n";
			cout << player1.name << ": " << player1.nummatcheswon << " matches won\n";
			cout << player2.name << ": " << player2.nummatcheswon << " matches won\n";
			cout << "Number of ties: " << nummatches - player1.nummatcheswon - player2.nummatcheswon << "\n";
		}
	}

	infile.close();
}