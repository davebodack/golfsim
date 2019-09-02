void international(Player golfers[], int golfernum) {

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

	while ((internationalinput != "Ryder Cup") && (internationalinput != "President's Cup") && (internationalinput != "Ryder cup") && (internationalinput != "Presidents Cup") && (internationalinput != "President's cup") && (internationalinput != "Presidents cup") && (internationalinput != "ryder cup") && (internationalinput != "president's cup") && (internationalinput != "presidents cup") && (internationalinput != "Ryder") && (internationalinput != "ryder") && (internationalinput != "Presidents") && (internationalinput != "presidents")) {
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
		cin.ignore();
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
			rydercuppointer = run_match(americans[i], internationals[i], 1, false);

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