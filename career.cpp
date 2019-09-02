void career(Player golfers[], int golfernum) {

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
	
}