void draft(Player golfers[], int golfernum) {

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
