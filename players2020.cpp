void players_2020(Player golfers[], int golfernum, int numtourneys) {

	string boardprint;
	cout << "Would you like to print the leaderboards after each round of every tournament?\n";
	cin >> boardprint;

	while ((!cin) && (boardprint != "Yes") && (boardprint != "No") && (boardprint != "YES") && (boardprint != "NO") && (boardprint != "yes") && (boardprint != "no") && (boardprint != "Y") && (boardprint != "N") && (boardprint != "y") && (boardprint != "n")) {
		cout << "Invalid input entered. Please type whether or not you would like to print the leaderboard after every round of every simulated tournament:\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin >> boardprint;
	}

	bool tourneyprintflag = false;
	if ((boardprint == "YES") || (boardprint == "Yes") || (boardprint == "yes") || (boardprint == "Y") || (boardprint == "y")) {
		tourneyprintflag = true;
	}

	cout << "\nSimulating tournament(s)... please wait\n";
	for (int i = 0; i < numtourneys; i++) {
		determine_scores(golfers, golfernum, 20, 72, 0, tourneyprintflag, 0);
		for (int j = 0; j < golfernum; j++) {
			//Allows resetting scores back to what they were in real life after Rd. 1
			golfers[j].score = golfers[j].originalscore;
		}
	}

	sort(golfers, golfernum);
	cout << "\nHere are the results of simulating " << numtourneys << " 2020 Players Championships:\n\n";
	cout << "                        |  Tournaments Won  |\n";
	for (int i = 0; i < golfernum; i++) {
		cout << golfers[i].name;
		for (int j = 0; j < 24 - golfers[i].name.size(); j++) {
			cout << " ";
		}
		cout << "|        ";
		if (golfers[i].pgatourwins > 99) {
			cout << golfers[i].pgatourwins << "        |\n";
		} else if (golfers[i].pgatourwins > 9) {
			cout << " " << golfers[i].pgatourwins << "        |\n";
		} else {
			cout << "  " << golfers[i].pgatourwins << "        |\n";
		}
	}

}