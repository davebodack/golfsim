void matchplay(Player golfers[]) {

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
