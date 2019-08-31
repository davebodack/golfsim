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

//Standard class for golfers in any simulation mode
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
	double draftpoints;
	double totaldraftpoints;
	bool draftedflag;

	//Standard default constructor
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
		draftedflag = false;
	}
};


//Adds together the ratings of golfers in an array and returns the sum
double sum(Player golfers[], int golfernum) {
	
	double sum = 0;

	for (int i = 0; i < golfernum; i++) {
		sum += golfers[i].rating;
	}
	return sum;
}


//Determines the winner of a stroke play tournament from an array of golfers and modifies the relevant attributes of that golfer
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


//Simplistic method of determining the winner of a match between two golfers. Returns true if golfer1 wins, false if golfer2 wins
bool determine_match_winner(Player golfer1, Player golfer2) {
	
	int matchratingsum = (int) (golfer1.matchrating + golfer2.matchrating + 0.5);
	return (rand() % matchratingsum) < golfer1.matchrating;
}


//Determines the winner of one hole in a match between two golfers. Returns 1 if golfer1 wins, 2 if they tie, and 3 if golfer2 wins
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


//Determines the winner of a foursome match. Returns 1 if golfers 1 and 2 win, 2 if the four of them tie, and 3 if golfers 3 and 4 win
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


//Prints details about a hole that depend on whether the hole had a victor or whether it was tied.
void print_hole_details(Player winninggolfer, Player losinggolfer, bool tieflag) {

	string details[30];
	details[0] = winninggolfer.name + " works his magic around the greens as he holes his bunker shot to win the hole.";
	details[1] = winninggolfer.name + "'s enourmous drive sets up a wedge shot that " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " sticks to 5 feet, and he makes the ticklish birdie putt to win the hole.";
	details[2] = "In a mano a mano battle, " + winninggolfer.name + " and " + losinggolfer.name + " play the hole almost exactly the same and end up with the same putts, but " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " misses his left and " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " gets the read to sink the putt and win the hole.";
	details[3] = "A superbly executed hole for " + winninggolfer.name + ", as he stripes his tee shot, flushes an 8-iron to within 10 feet, and casually makes the birdie putt to win the hole.";
	details[4] = "Incredible luck for " + winninggolfer.name + "! An approach shot headed for the bunker takes a wild carom off the lip that rolls three feet from the cup, and that'll give " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " the hole.";
	details[5] = "Like baseball, the other half of golf may be physical, but 90\% of it is mental. That's why " + winninggolfer.name + "'s courage and mental fortitude paid off, as his aggressive angle to the hole off the tee left him a much shorter approach shot and led to him winning the hole.";
	details[6] = "A boisterous fan engages " + winninggolfer.name + " in some good-natured verbal jousting as he walks to the tee box, which seems to inspire " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " as he crushes his farthest drive of the day. The joyous cheering of " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + "'s fans propels him to an emphatic victory of the hole over " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + ".";
	details[7] = "There was no stopping " + winninggolfer.name + " on this hole. An ill-timed and thoughtless shout during " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + "'s downswing made his caddie and course marshals furious, but " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " seemed unperturbed as he walked after his gorgeous tee shot and went on to handily take the hole from " + losinggolfer.name + ".";
	details[8] = "When you're on, you're on. " + winninggolfer.name + " wowed the crowd by almost holing his approach to the green, giving him a tap-in that he sunk to win the hole over " + losinggolfer.name + ".";
	details[9] = "I wonder if he meant to do that. " + winninggolfer.name + "'s second shot seemed to barely leave the ground as it rocketed towards the hole, but this skillful avoidance of suddenly gusting winds allowed him to reach the green when " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " could not. This made all the difference for " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + ", as he went on to win the hole.";
	
	details[10] = losinggolfer.name + "'s 15-foot putt just misses on the low side, giving " + winninggolfer.name + " the hole.";
	details[11] = losinggolfer.name + " loses it way right off the tee, and a skillful recovery shot after his drop won't be enough for " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " as he loses the hole to " + winninggolfer.name + ".";
	details[12] = "Trouble for " + losinggolfer.name + " around the greens as his chunked chip falls woefully short and his two-putt bogey hands " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " the hole.";
	details[13] = losinggolfer.name + "'s approach shot succumbs to the green's false front, and although he pitches it to seven feet, " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " misses the par putt and loses the hole.";
	details[14] = losinggolfer.name + " must have ate one too many bowls of Wheaties this morning: his seemingly miscalculated approach shot sails over the green, a costly error that hands " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " the hole.";
	details[15] = "This hole was no match for either golfer. It looked as if two birdies were on the way, only for " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + "'s ball to lip out from only six feet. A painful loss, and a very lucky break for " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + ".";
	details[16] = losinggolfer.name + "'s tee shot settles in some pine straw off the left side of the fairway, and judging by the poor quality of his second shot and his wincing afterwards, it seems he struck a root when he hit the ball. Unfortunately, these misadventures will cost " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " the hole.";
	details[17] = "It just wasn't " + losinggolfer.name + "'s hole. His tee shot landed in a fairway bunker, and his most valiant efforts to salvage the hole after that misstep did " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " no good. His long par putt slid just past the hole, making " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + "the hole's victor.";
	details[18] = "A tough hole to watch for fans of " + losinggolfer.name + ". The golfing legend seemed to shake his head after every shot, and those nearby the green after he missed his short bogey putt to lose the hole heard him mutter in disgust of his play. Hopefully " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " gets his mind right for the next hole.";
	details[19] = "A phenomenally bad break for " + losinggolfer.name + ". His ball seemed to have settled four or five paces from the hole, only for it to inexplicably catch the slope of the green as " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " approached the green and roll onto the fairway. Being the tenacious golfer he is, " + winninggolfer.name + " took advantage of this and sunk a clutch birdie putt to win the hole.";
	
	details[20] = "These two golfers have played incredible golf against each other in the past, but 'incredible' isn't a word that comes to mind when describing this hole. " + winninggolfer.name + " and " + losinggolfer.name + " both make sloppy bogeys, leaving them tied for the hole.";
	details[21] = "Golf is a funny game. " + winninggolfer.name + " seemed to have the hole in the bag, but after " + losinggolfer.name + " sunk an amazing 35-foot par putt, " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " pushed his five-foot birdie putt and never gave it a chance. The two golfers end up splitting the hole.";
	details[22] = "A ho-hum hole for both players, as neither " + winninggolfer.name + " nor " + losinggolfer.name + " is able to get their approach shots close to the green. Two two-putts lead to " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " and " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " tying the hole.";
	details[23] = winninggolfer.name + " may have outdriven " + losinggolfer.name + " by a considerable margin, but there's a reason you drive for show and putt for dough. " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " sinks a 25-foot birdie putt right before " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " cleans up his putt for birdie to tie the hole.";
	details[24] = "Trouble for both players off the tee: " + winninggolfer.name + " lands in thick rough that he's barely able to whack it out of, and " + losinggolfer.name + " ends up hitting an unfortunate fan in the gallery. After a barrage of apologies and an autographed glove, both players bogey the hole.";
	details[25] = "A solid drive from both players, although " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + "'s seemed to carry just a little farther. Regardless, both players are able to put it on the green and two-putt for a routine par.";
	details[26] = losinggolfer.name + " seemed as surprised as everyone else at the atypical ball flight on his approach shot. His shot may have barely left the ground, but it rolled right up to the green and gave " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " a birdie putt that he'd make to tie the hole with " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + ".";
	details[27] = "Both players are able to get it done from different less-than-ideal spots around the green. " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " perfectly places his chip from the basin his ball rolled into, and " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " makes a superb sand shot that he taps in for par, as " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " does also to tie the hole.";
	details[28] = "These two are not letting the pressure of the moment get to them. " + winninggolfer.name + " and " + losinggolfer.name + " both crush their tee shots and flush 3-irons that roll onto the edge of the green on this par-5. Neither golfer can shake the other on this hole, however, as " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + " and " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " both two-putt to tie the hole.";
	details[29] = "What looked like a horrific tee shot from " + losinggolfer.name + " took a wild kick off a tree branch into the middle of the fairway. " + losinggolfer.name.substr(losinggolfer.name.find(" ") + 1) + " could only shake his head and smile, and perhaps bolstered by his luck, he manages to birdie the hole to tie the hole with " + winninggolfer.name.substr(winninggolfer.name.find(" ") + 1) + ".";

	int randdetail;
	if (tieflag == false) {
		randdetail = rand() % 20;
	} else {
		randdetail = (rand() % 10) + 20;
	}

	cout << details[randdetail] << "\n\n";

}

//Runs a number of match play matches specified by nummatches. 
//Calls determine_hole_winner appropriate number of times in order to determine match results.
//Returns pointer to an array containing the golfers in the match with the appropriate attributes updated.
Player* run_match(Player golfer1, Player golfer2, int nummatches, bool detailsflag) {

	double ratingavg = (golfer1.rating + golfer2.rating) / 2;
	golfer1.matchrating = (golfer1.rating + ratingavg) / 2;
	golfer2.matchrating = (golfer2.rating + ratingavg) / 2;

	for (int i = 0; i < nummatches; i++) {
		bool victoryflag = false;
		int roundsum = 0;
		int numholesleft = 18;
		int holeresult = 0;
		for (int j = 1; j < 19; j++) {
			holeresult = determine_hole_winner(golfer1, golfer2);
			numholesleft--;

			if (victoryflag == false) {
				if (holeresult == 1) {
					roundsum--;
					if (detailsflag == true) {
						print_hole_details(golfer1, golfer2, false);
					}
				} else if (holeresult == 2) {
					if (detailsflag == true) {
						print_hole_details(golfer1, golfer2, true);
					}
				} else {
					roundsum++;
					if (detailsflag == true) {
						print_hole_details(golfer2, golfer1, false);
					}
				}

				if (detailsflag == true) {
					if (roundsum < 0) {
						cout << "After " << j << " holes, " << golfer1.name << " is up by " << abs(roundsum) << ".\n\n";
					} else if (roundsum > 0) {
						cout << "After " << j << " holes, " << golfer2.name << " is up by " << abs(roundsum) << ".\n\n";
					} else {
						cout << "After " << j << " holes, " << golfer1.name << " and " << golfer2.name << " are all tied up.\n\n";
					}
				}
			}

			if ((abs(roundsum) > numholesleft) && (victoryflag == false)) {
				victoryflag = true;
				if (roundsum < 0) {
					golfer1.nummatcheswon++;
					if (nummatches == 1) {
						cout << golfer1.name << " defeats " << golfer2.name << " " << abs(roundsum) << " & " << numholesleft << "!\n";
					}
				} else if (roundsum > 0){
					golfer2.nummatcheswon++;
					if (nummatches == 1) {
						cout << golfer2.name << " defeats " << golfer1.name << " " << abs(roundsum) << " & " << numholesleft << "!\n";
					}	
				}
			}
		}

		if ((roundsum == 0) && (nummatches == 1)) {
			golfer1.nummatchestied++;
			golfer2.nummatchestied++;
			cout << golfer1.name << " and " << golfer2.name << " tie the match.\n";
			
		}
	}

	Player* matchreturngolfers = new Player[2];
	matchreturngolfers[0] = golfer1;
	matchreturngolfers[1] = golfer2;
	return matchreturngolfers;
}


//Randomly shuffles an array of golfers
void shuffle(Player golfers[], int golferssize) {

	for (int i = 0; i < golferssize; i++) {
		int index = rand() % (golferssize - 1);
		swap(golfers[i], golfers[index]);
	}
}


//Swaps the addresses of two golfers
void swap(Player& x, Player& y) {
	
	Player temp;
	temp = x;
	x = y;
	y = temp;
}


//Sorts an array of golfers based on the number of majors the golfers have won
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


//Sorts an array of golfers based on the number of tournaments in Career Mode that the golfers have won
void match_sort(Player golfers[], int golfernum) {
	
	for (int num = 1; num < golfernum; num++) {
		for (int i = 0; i < golfernum - num; i++) {
			if (golfers[i].numtourneyswon < golfers[i+1].numtourneyswon) {
				swap(golfers[i], golfers[i+1]);
			}
		}
	}
}


//Sorts an array of golfers based on the number of Ryder Cup points that the golfers have accrued
void ryder_cup_sort(Player golfers[]) {

	for (int num = 1; num < 12; num++) {
		for (int i = 0; i < 12 - num; i++) {
			if (golfers[i].totalrydercuppoints < golfers[i+1].totalrydercuppoints) {
				swap(golfers[i], golfers[i+1]);
			}
		}
	}
}


//Sorts an array of golfers based on the number of points in a draft competition that the golfers have accrued
void draft_sort(Player golfers[]) {

	for (int num = 1; num < 12; num++) {
		for (int i = 0; i < 12 - num; i++) {
			if (golfers[i].totaldraftpoints < golfers[i+1].totaldraftpoints) {
				swap(golfers[i], golfers[i+1]);
			}
		}
	}
}

//The main function prompts the user to choose the mode of simulation they would like to execute,
//and executes each form of simulation based on what the user selects
int main(int argc, char* argv[]) {

	cout << "\nWelcome! This is the Historical Golf Legend Simulator.\n\n";
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

		while ((!cin) || (numtourneys < 1)) {
			cout << "Invalid number of tournaments entered. Please enter a number of tournaments greater than zero that you'd like to simulate:\n";
			cin >> numtourneys;
		}

		double ratingavg;
		Player golfer1;
		Player golfer2;
		bool detailsflag = false;

		for (int i = 0; i < numtourneys; i++) {
			
			detailsflag = false;

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
			detailsflag = true;

			Player *tourneyfinale = run_match(matchgolfersrd6[0], matchgolfersrd6[1], 1, true);
			matchgolfersrd6[0] = tourneyfinale[0];
			matchgolfersrd6[1] = tourneyfinale[1];
			if (matchgolfersrd6[0].nummatcheswon > matchgolfersrd6[1].nummatcheswon) {
				cout << matchgolfersrd6[0].name << " defeats " << matchgolfersrd6[1].name << " in the final round to emerge victorious at the Legends Match Play Championship!" << '\n' << '\n';
				for (int i = 0; i < matchgolfernum; i++) {
					if (matchgolfersrd1[i].name == matchgolfersrd6[0].name) {
						matchgolfersrd1[i].numtourneyswon++;
					}
				}
			}
			else if (matchgolfersrd6[0].nummatcheswon == matchgolfersrd6[1].nummatcheswon) {
				cout << matchgolfersrd6[1].name << " and " << matchgolfersrd6[0].name << " tie in the final round of the Legends Match Play Championship!" << '\n' << '\n';
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

		Player *matchpointer;
		matchpointer = run_match(player1, player2, nummatches, true);
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
		shuffle(americans, 12);
		shuffle(internationals, 12);
		
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

				shuffle(americans, 12);
				shuffle(internationals, 12);
			}

			shuffle(americans, 12);
			shuffle(internationals, 12);

			for (int i = 0; i < 12; i++) {
				americans[i].nummatcheswon = 0;
				internationals[i].nummatcheswon = 0;
				americans[i].nummatchestied = 0;
				internationals[i].nummatchestied = 0;

				Player *rydercuppointer;
				rydercuppointer = run_match(americans[i], internationals[i], 1, true);

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

	else if ((input == "Draft") || (input == "draft")) {
		
		int numplayersdraft;
		cout << "\nHow many players would you like to be on each team?\n";
		cin >> numplayersdraft;

		while ((numplayersdraft < 2) || (numplayersdraft > 12)) {
			cout << "Invalid number of players entered. Please enter a number of players that is at least 2 and no more than 12.\n";
			cin >> numplayersdraft;
		}

		string capresponse;
		double pointscap = 0;
		cout << "Would you like to have a cap on the amount of points available for each person to draft players with? (Y/N)\n";
		cin >> capresponse;

		while ((capresponse != "YES") && (capresponse != "NO") && (capresponse != "Yes") && (capresponse != "No") && (capresponse != "yes") && (capresponse != "no") && (capresponse != "Y") && (capresponse != "N") && (capresponse != "y") && (capresponse != "n")) {
			cout << "Invalid response. Please indicate whether you would like to have a cap on the amount of points available for each person to draft players with by typing 'Yes' or 'No'.\n";
			cin >> capresponse;
		}

		bool capresponseyes = false;
		if ((capresponse == "YES") || (capresponse == "Yes") || (capresponse == "yes") || (capresponse == "Y") || (capresponse == "y")) {
			capresponseyes = true;
		}	

		if (capresponseyes == true) {
			for (int i = 0; i < (numplayersdraft * 2); i = i+2) {
				pointscap += golfers[i].rating * .75;
			}
			cout << "The maximum number of points that can be spent by each person to draft a golfer onto their team is: " << pointscap << "\n\n";
		} else {
			pointscap = 10000000;
		}

		Player draftteam1[numplayersdraft];
		Player draftteam2[numplayersdraft];
		double pointsleft[2];
		pointsleft[0] = pointscap;
		pointsleft[1] = pointscap;
		string draftinput;
		string draftedplayers[numplayersdraft * 2];

		cout << "\nThese are the players that are available to draft";
		if (capresponseyes == true) {
			cout << " and the number of points needed to draft them";
		}
		cout << ":\n\n";

		for (int i = 0; i < golfernum; i++) {
			cout << golfers[i].name;
			if (capresponseyes == true) {
				cout << ": " << golfers[i].rating;
			}
			cout << "\n";
		}
		cout << "\nThose are the players available to draft.\n";

		for (int i = 0; i < numplayersdraft; i++) {	
			for (int j = 0; j < 2; j++) {
				
				cout << "\nPlayer " << j + 1 << ", it's your turn to draft. ";
				if (capresponseyes == true) {
					cout << "You have " << pointsleft[j] << " left to draft with. ";
				}

				if (i > 0) {
					cout << "\nHere's who you've already picked:\n";
					for (int z = 0; z < i; z++) {
						if (j == 0) {
							cout << draftteam1[z].name << '\n';
						} else {
							cout << draftteam2[z].name << '\n';
						}
					}
				}

				cout << "\nWho would you like to pick next?\n";
				cout.flush();

				bool founddraftpick = false;
				cin.ignore();
				getline(cin, draftinput);

				while (founddraftpick == false) {
					for (int n = 0; n < golfernum; n++) {
						if ((draftinput == golfers[n].name) || (draftinput == golfers[n].name.substr(1))) { //|| ((draftinput == golfers[n].name.substr(golfers[n].name.find(" ") + 1)) && samelastname == false)
							if (golfers[n].draftedflag == true) {
								cout << "\nYou can't pick them, they've already been picked!";
							} else if (pointsleft[j] - golfers[n].rating < 0) {
								cout << "\nYou don't have enough points left to pick them.";
							} else {
								founddraftpick = true;
								golfers[n].draftedflag = true;
								pointsleft[j] -= golfers[n].rating;
								if (j == 0) {
									draftteam1[i] = golfers[n];
								} else {
									draftteam2[i] = golfers[n];
								}
								cout << "\nPlayer " << j + 1 << ", you drafted " << golfers[n].name << ".\n";
							}
						}
					}

					if (founddraftpick == false) {
						cout << "\nInvalid player name entered. Choose a player you'd like to draft:\n";
						cin.ignore();
						getline(cin, draftinput);
					}
				}
			}
		}

		cout << "\n\nThe draft is over! Here are the golfers on each team.\n\n";
		cout << "Team 1:\n";
		for (int i = 0; i < numplayersdraft; i++) {
			cout << draftteam1[i].name << "\n";
		}

		cout << "\nTeam 2:\n";
		for (int i = 0; i < numplayersdraft; i++) {
			cout << draftteam2[i].name << "\n";
		}

		cout << "\nEach match between these two teams will take place over four days.\n";
		cout << "In each match, every player will face off in match play against a random player on the other team.\n\n";
		
		int numdraftmatches;
		cout << "How many matches would you like these teams to play against each other?\n";
		cin >> numdraftmatches;

		while (numdraftmatches < 1) {
			cout << "Invalid number of matches entered. Please, do me a favor and enter a valid number of matches for the teams to play against each other.\n";
			cin >> numdraftmatches;
		}

		double team1points = 0;
		double team2points = 0;
		double team1totalpoints = 0;
		double team2totalpoints = 0;
		int team1matcheswon = 0;
		int team2matcheswon = 0;

		srand(time(NULL));

		for (int i = 0; i < numdraftmatches; i++) {

			team1points = 0;
			team2points = 0;

			for (int i = 0; i < 4; i++) {

				if (numplayersdraft == 2){
					swap(draftteam1[0], draftteam1[1]);
				} else {
					shuffle(draftteam1, numplayersdraft);
					shuffle(draftteam2, numplayersdraft);
				}

				if (numdraftmatches == 1) {
					cout << "\nHere are the results for Day " << i + 1 << ":\n";
				}

				for (int j = 0; j < numplayersdraft; j++) {
					draftteam1[j].nummatcheswon = 0;
					draftteam1[j].nummatchestied = 0;
					draftteam2[j].nummatcheswon = 0;
					draftteam2[j].nummatchestied = 0;

					Player *draftmatchresult = run_match(draftteam1[j], draftteam2[j], 1, false);
					draftteam1[j] = draftmatchresult[0];
					draftteam2[j] = draftmatchresult[1];

					if (draftteam1[j].nummatchestied == 1) {
						draftteam1[j].draftpoints += 0.5;
						team1points += 0.5;
						draftteam2[j].draftpoints += 0.5;
						team2points += 0.5;
					} else {
						draftteam1[j].draftpoints = draftteam1[j].nummatcheswon;
						team1points += draftteam1[j].nummatcheswon;
						draftteam2[j].draftpoints = draftteam2[j].nummatcheswon;
						team2points += draftteam2[j].nummatcheswon;
					}

					draftteam1[j].totaldraftpoints += draftteam1[j].draftpoints;
					draftteam2[j].totaldraftpoints += draftteam2[j].draftpoints;
				}
			}

			if (team1points > team2points) {
				team1matcheswon++;
				cout << "\nTeam 1 emerges victorious over Team 2, winning the match " << team1points << " points to " << team2points << "!\n\n";
			} else if (team2points > team1points) {
				team2matcheswon++;
				cout << "\nTeam 2 emerges victorious over Team 1, winning the match " << team2points << " points to " << team1points << "!\n\n";
			} else {
				cout << "\nTeam 1 and Team 2 end the match dead even, " << team1points << " points apiece!\n\n";
			}
		}

		if (numdraftmatches > 1) {
			if (team1matcheswon > team2matcheswon) {
				cout << "\nTeam 1 takes the cake in this competition, winning " << team1matcheswon << " matches to Team 2's " << team2matcheswon << ".\n\n";
			} else if (team2matcheswon > team1matcheswon) {
				cout << "\nTeam 2 takes the cake in this competition, winning " << team2matcheswon << " matches to Team 1's " << team1matcheswon << ".\n\n";
			} else {
				cout << "\nNeither team could prove their superiority over the other in this competition, with Team 1 and Team 2 both winning " << team1matcheswon << " matches.\n\n";
			}
		}
	}

	infile.close();
}

