void oneonone(Player golfers[], int golfernum) {
	
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
	if (nummatches == 1) {
		matchpointer = run_match(player1, player2, nummatches, true);
	} else {
		matchpointer = run_match(player1, player2, nummatches, false);
	}
	player1 = matchpointer[0];
	player2 = matchpointer[1];

	if (nummatches > 1) {
		cout << "\nNumber of matches: " << nummatches << "\n";
		cout << player1.name << ": " << player1.nummatcheswon << " matches won\n";
		cout << player2.name << ": " << player2.nummatcheswon << " matches won\n";
		cout << "Number of ties: " << nummatches - player1.nummatcheswon - player2.nummatcheswon << "\n";
	}
}