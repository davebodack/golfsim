//Author: David Bodack

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
	int nummatchesplayed;
	int nummatcheswon;
	int nummatchestied;
	double rydercuppoints;
	double totalrydercuppoints;

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
		nummatchesplayed = 0;
		nummatcheswon = 0;
		rydercuppoints = 0;
		totalrydercuppoints = 0;
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
}


int determine_foursome_winner(Player golfer1, Player golfer2, Player golfer3, Player golfer4) {
	
	int foursomerating = (golfer1.rating + golfer2.rating + golfer3.rating + golfer4.rating) / 4;
	golfer1.matchrating = (golfer1.rating + foursomerating) / 2;
	golfer2.matchrating = (golfer2.rating + foursomerating) / 2;
	golfer3.matchrating = (golfer3.rating + foursomerating) / 2;
	golfer4.matchrating = (golfer4.rating + foursomerating) / 2;

	int foursomematchratingsum = (int) (golfer1.matchrating + golfer2.matchrating + golfer3.matchrating + golfer4.matchrating + 0.5);
	int foursomerandnum = (rand() % foursomematchratingsum);

	if (foursomerandnum < (golfer1.matchrating + golfer2.matchrating)) {
		return 1;
	} else if (foursomerandnum < (foursomematchratingsum - (golfer3.matchrating + golfer4.matchrating))) {
		return 2;
	} else {
		return 3;
	}
}


Player* run_match(Player golfer1, Player golfer2, int nummatches, bool printflag) {

	double ratingavg = (golfer1.rating + golfer2.rating) / 2;
	golfer1.matchrating = (golfer1.rating + ratingavg) / 2;
	golfer2.matchrating = (golfer2.rating + ratingavg) / 2;

	for (int i = 0; i < nummatches; i++) {
		bool victoryflag = false;
		int roundsum = 0;
		int numholesleft = 18;
		int holeresult = 0;
		for (int i = 1; i < 19; i++) {
			holeresult = determine_hole_winner(golfer1, golfer2);
			numholesleft--;

			if (holeresult == 1) {
				roundsum--;
			} else if (holeresult == 3) {
				roundsum++;
			}

			if ((abs(roundsum) > numholesleft) && (victoryflag == false)) {
				victoryflag = true;
				if (roundsum < 0) {
					golfer1.nummatcheswon++;
					if ((nummatches == 1) && (printflag == true)) {
						cout << golfer1.name << " defeats " << golfer2.name << " " << abs(roundsum) << " & " << numholesleft << "!\n";
					}
				}
				else {
					golfer2.nummatcheswon++;
					if ((nummatches == 1) && (printflag == true)) {
						cout << golfer2.name << " defeats " << golfer1.name << " " << abs(roundsum) << " & " << numholesleft << "!\n";
					}	
				}
			}
		}

		if ((roundsum == 0) && (nummatches == 1)) {
			golfer1.nummatchestied++;
			golfer2.nummatchestied++;
			if (printflag == true) {
				cout << golfer1.name << " and " << golfer2.name << " tie the match.\n";
			}
		}
	}

	Player* matchreturngolfers = new Player[2];
	matchreturngolfers[0] = golfer1;
	matchreturngolfers[1] = golfer2;
	return matchreturngolfers;
}


void shuffle(Player golfers[]) {

	for (int i = 0; i < 12; i++) {
		int index = rand() % 12;
		Player tempgolfer = golfers[i];
		golfers[i] = golfers[index];
		golfers[index] = tempgolfer;
	}
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


void ryder_cup_sort(Player golfers[]) {

	for (int num = 1; num < 12; num++) {
		for (int i = 0; i < 12 - num; i++) {
			if (golfers[i].totalrydercuppoints < golfers[i+1].totalrydercuppoints) {
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
	cout << "If you'd like to simulate a full career, type 'career'. If you'd like to simulate a match play tournament, type 'match play'. If you'd like to draft a golfer and play a match against someone, type 'one on one'. If you'd like to simulate an all-time Ryder Cup or Presidents Cup, type 'International'.\n"; 
	getline(cin, input);

	while ((input != "Career") && (input != "career") && (input != "match play") && (input != "Match play") && (input != "Match Play") && (input != "one on one") && (input != "1 on 1") && (input != "One on One") && (input != "One On One") && (input != "Ryder Cup") && (input != "International") && (input != "international") && (input != "intl")) {
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

	else if ((input == "one on one") || (input == "1 on 1") || (input == "One on One") || (input == "One On One")) {
		
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

		bool oneononeprintflag = false;
		if (nummatches == 1) {
			oneononeprintflag = true;
		}

		Player *matchpointer;
		matchpointer = run_match(player1, player2, nummatches, oneononeprintflag);
		player1 = matchpointer[0];
		player2 = matchpointer[1];

		if (nummatches > 1) {
			cout << "\nNumber of matches: " << nummatches << "\n";
			cout << player1.name << ": " << player1.nummatcheswon << " matches won\n";
			cout << player2.name << ": " << player2.nummatcheswon << " matches won\n";
			cout << "Number of ties: " << nummatches - player1.nummatcheswon - player2.nummatcheswon << "\n";
		}
	}

	else if ((input == "International") || (input == "international") || (input == "intl")) {
		
		Player americans[12];
		Player internationals[12];
		int americancounter = 0;
		int internationalcounter = 0;
		double american_points;
		double international_points;
		int americanrydercupswon = 0;
		int internationalrydercupswon = 0;

		string internationalinput;
		char internationaltype;

		cout << "\nIf you'd like to simulate a Ryder Cup, type 'Ryder Cup'. If you'd like to simulate a President's Cup, type 'President's Cup'.\n";
		cin >> internationalinput;

		while ((internationalinput != "Ryder Cup") && (internationalinput != "President's Cup") && (internationalinput != "ryder cup") && (internationalinput != "president's cup") && (internationalinput != "presidents cup") && (internationalinput != "Ryder") && (internationalinput != "ryder") && (internationalinput != "Presidents") && (internationalinput != "presidents")) {
			cout << "Invalid input entered, please select either the Ryder Cup by typing 'Ryder Cup' or the President's Cup by typing 'President's Cup'.\n";
			cin >> internationalinput;
		}

		if ((internationalinput == "Ryder Cup") || (internationalinput == "ryder cup") || (internationalinput == "Ryder") || (internationalinput == "ryder")) {
			internationaltype = 'E';
		} else {
			internationaltype = 'R';
		}

		for (int i = 0; i < golfernum; i++) {
			if ((golfers[i].nationality == 'A') && (americancounter < 12)) {
				americans[americancounter] = golfers[i];
				americancounter++;
			} else if ((golfers[i].nationality == internationaltype) && (internationalcounter < 12)) {
				internationals[internationalcounter] = golfers[i];
				internationalcounter++;
			}
		}

		srand(time(0));
		shuffle(americans);
		shuffle(internationals);
		
		int numrydercups;
		if (internationaltype == 'E') {
			cout << "\nHow many Ryder Cups would you like to simulate?\n";
		} else {
			cout << "\nHow many President's Cups would you like to simulate?\n";
		}
		cin >> numrydercups;

		while ((!cin) && (numrydercups < 1)) {
			if (internationaltype == 'E') {
				cout << "Invalid number of Ryder Cups entered. Please enter a valid number of Ryder Cups to be simulated:\n";
			} else {
				cout << "Invalid number of President's Cups entered. Please enter a valid number of President's Cups to be simulated:\n";
			}
			cin >> numrydercups;
		}

		bool rydercupprintflag = false;
		if (numrydercups == 1) {
			rydercupprintflag = true;
		}

		for (int n = 0; n < numrydercups; n++) {

			for (int x = 0; x < 12; x++) {
				americans[x].rydercuppoints = 0;
				americans[x].nummatcheswon = 0;
				americans[x].nummatchestied = 0;
				internationals[x].rydercuppoints = 0;
				internationals[x].nummatcheswon = 0;
				internationals[x].nummatchestied = 0;
			}

			for (int i = 0; i < 4; i++) {

				american_points = 0;
				international_points = 0;

				for (int j = 0; j < 8; j += 2) {
					int fourball_result = determine_foursome_winner(americans[j], americans[j+1], internationals[j], internationals[j+1]);
					americans[j].nummatchesplayed++;
					americans[j+1].nummatchesplayed++;
					internationals[j].nummatchesplayed++;
					internationals[j+1].nummatchesplayed++;
					if (fourball_result == 1) {
						americans[j].rydercuppoints++;
						americans[j+1].rydercuppoints++;
						if (numrydercups == 1) {
							cout << americans[j].name << " and " << americans[j+1].name << " defeat " << internationals[j].name << " and " << internationals[j+1].name << ".\n";
						}
					} else if (fourball_result == 2) {
						americans[j].rydercuppoints += 0.5;
						internationals[j].rydercuppoints += 0.5;
						if (numrydercups == 1) {
							cout << americans[j].name << " and " << americans[j+1].name << " tie " << internationals[j].name << " and " << internationals[j+1].name << ".\n";
						}
					} else {
						internationals[j].rydercuppoints++;
						internationals[j+1].rydercuppoints++;
						if (numrydercups == 1) {
							cout << internationals[j].name << " and " << internationals[j+1].name << " defeat " << americans[j].name << " and " << americans[j+1].name << ".\n";
						}
					}
				}

				for (int i = 0; i < 12; i++) {
					american_points += americans[i].rydercuppoints;
					international_points += internationals[i].rydercuppoints;
				}

				cout << '\n';

				if ((i == 1) || (i == 3)) {
					american_points /= 2;
					international_points /= 2;

					if (numrydercups == 1) {
						if (american_points > international_points) {
							if (internationaltype == 'E') {
								cout << "After Day " << ((i / 2) + 1) << ", the Americans lead the Europeans, " << american_points << "-" << international_points << "!\n\n";
							} else {
								cout << "After Day " << ((i / 2) + 1) << ", the Americans lead the Internationals, " << american_points << "-" << international_points << "!\n\n";
							}
						} else if (american_points == international_points) {
							if (internationaltype == 'E') {
								cout << "After Day " << ((i / 2) + 1) << ", the Americans and the Europeans are tied at " << american_points << "!\n\n"; 
							} else {
								cout << "After Day " << ((i / 2) + 1) << ", the Americans and the Internationals are tied at " << american_points << "!\n\n"; 
							}
						} else {
							if (internationaltype == 'E') {
								cout << "After Day " << ((i / 2) + 1) << ", the Europeans lead the Americans, " << international_points << "-" << american_points << "!\n\n";
							} else {
								cout << "After Day " << ((i / 2) + 1) << ", the Internationals lead the Americans, " << international_points << "-" << american_points << "!\n\n";
							}
						}
					}
				}

				shuffle(americans);
				shuffle(internationals);
			}

			shuffle(americans);
			shuffle(internationals);

			for (int i = 0; i < 12; i++) {
				americans[i].nummatcheswon = 0;
				internationals[i].nummatcheswon = 0;
				americans[i].nummatchestied = 0;
				internationals[i].nummatchestied = 0;

				Player *rydercuppointer;
				rydercuppointer = run_match(americans[i], internationals[i],1, rydercupprintflag);

				americans[i] = rydercuppointer[0];
				internationals[i] = rydercuppointer[1];
				americans[i].nummatchesplayed++;
				internationals[i].nummatchesplayed++;

				if (americans[i].nummatchestied == 1) {
					americans[i].rydercuppoints += 0.5;
					american_points += 0.5;
					internationals[i].rydercuppoints += 0.5;
					international_points += 0.5;
				} else {
					americans[i].rydercuppoints += americans[i].nummatcheswon;
					american_points += americans[i].nummatcheswon;
					internationals[i].rydercuppoints += internationals[i].nummatcheswon;
					international_points += internationals[i].nummatcheswon;
				}

				americans[i].totalrydercuppoints += americans[i].rydercuppoints;
				internationals[i].totalrydercuppoints += internationals[i].rydercuppoints;
			}

			ryder_cup_sort(americans);
			ryder_cup_sort(internationals);

			if (numrydercups == 1) {
				cout << "\nFinal points tally:\n";
				for (int i = 0; i < 12; i++) {
					cout << americans[i].name << ": " << americans[i].nummatchesplayed << " matches, " << americans[i].rydercuppoints  << " points";
					for (int j = 0; j < 17 - americans[i].name.size(); j++) {
						cout << " ";
					}
					cout << "| " << internationals[i].name << ": " << internationals[i].nummatchesplayed << " matches, " << internationals[i].rydercuppoints << " points\n";
				}
			}


			if (american_points > international_points) {
				americanrydercupswon++;
				if (internationaltype == 'E') {
					cout << "\nThe Americans emerge victorious at the Ryder Cup, defeating the Europeans " << american_points << " to " << international_points << "!\n";
				} else {
					cout << "\nThe Americans emerge victorious at the Ryder Cup, defeating the Internationals " << american_points << " to " << international_points << "!\n";
				}
			} else if (american_points == international_points) {
				if (internationaltype == 'E') {
					cout << "\nThe Americans and the Europeans end up deadlocked in a tie, 14 to 14!\n";
				} else {
					cout << "\nThe Americans and the Internationals end up deadlocked in a tie, 14 to 14!\n";
				}
			} else {
				internationalrydercupswon++;
				if (internationaltype == 'E') {
					cout << "\nThe Europeans emerge victorious at the Ryder Cup, defeating the Americans " << international_points << " to " << american_points << "!\n";
				} else {
					cout << "\nThe Internationals emerge victorious at the Ryder Cup, defeating the Americans " << international_points << " to " << american_points << "!\n";
				}
			}
		}

		if (numrydercups > 1) {
			cout << "\nFinal points tally:\n";
			for (int i = 0; i < 12; i++) {
				cout << americans[i].name << ": " << americans[i].nummatchesplayed << " matches, " << americans[i].totalrydercuppoints  << " points";
				for (int j = 0; j < 17 - americans[i].name.size(); j++) {
					cout << " ";
				}
				cout << "| " << internationals[i].name << ": " << internationals[i].nummatchesplayed << " matches, " << internationals[i].totalrydercuppoints << " points\n";
			}
			if (numrydercups > 1) {
				if (internationaltype == 'E') {
					cout << "\nThe Americans win " << americanrydercupswon << " Ryder Cups and the Europeans win " << internationalrydercupswon << " Ryder Cups, with " << (numrydercups - americanrydercupswon - internationalrydercupswon) << " Ryder Cups tied between them.\n\n";
				} else {
					cout << "\nThe Americans win " << americanrydercupswon << " Ryder Cups and the Internationals win " << internationalrydercupswon << " Ryder Cups, with " << (numrydercups - americanrydercupswon - internationalrydercupswon) << " Ryder Cups tied between them.\n\n";
				}
			}
		}
	}

	infile.close();
}

