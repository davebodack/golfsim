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

	int numyears;
	cout << "How many years would you like to simulate? (20 years is recommended to simulate a full career):\n";
	cin >> numyears;

	while ((!cin) || (numyears < 1)) {
		cout << "Invalid number of years entered, please type how many years you'd like to simulate:\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin >> numyears;
	}

	string tourneyprintresp;
	cout << "Would you like to print out the winners of each tournament?\n";
	cin >> tourneyprintresp;

	while ((tourneyprintresp != "YES") && (tourneyprintresp != "NO") && (tourneyprintresp != "Yes") && (tourneyprintresp != "No") && (tourneyprintresp != "yes") && (tourneyprintresp != "no") && (tourneyprintresp != "Y") && (tourneyprintresp != "N") && (tourneyprintresp != "y") && (tourneyprintresp != "n")) {
		cout << "Invalid response. Please indicate whether you'd like to print the winners of each tournament by typing Yes or No:\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cin >> tourneyprintresp;
	}

	bool tourneyprintflag = false;
	if ((tourneyprintresp == "YES") || (tourneyprintresp == "Yes") || (tourneyprintresp == "yes") || (tourneyprintresp == "Y") || (tourneyprintresp == "y")) {
		tourneyprintflag = true;
	}

	Player winner;
	double regulartourneyscores[] = {500, 300, 190, 135, 110, 100, 90, 85, 80, 75, 70, 65, 60, 57, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35.5, 34, 32.5, 31, 29.5, 28, 26.5, 25, 23.5, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10.5, 10, 9.5, 9, 8.5, 8, 7.5, 7, 6.5, 6, 5.8, 5.6, 5.4, 5.2, 5, 4.8, 4.6, 4.4, 4.2, 4, 3.8, 3.6, 3.4, 3.2, 3, 2.9, 2.8, 2.7, 2.6, 2.5, 2.4, 2.3, 2.2, 2.1, 2, 1.9, 1.8, 1.7, 1.6, 1.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double wgcfedexscores[] = {550, 315, 200, 140, 115, 105, 95, 89, 83, 78, 73, 69, 65, 62, 59, 57, 55, 53, 52, 51, 48.73, 46.47, 44.2, 41.93, 40.23, 38.53, 36.83, 35.13, 33.43, 31.73, 30.03, 28.33, 26.63, 24.93, 23.8, 22.67, 21.53, 20.4, 19.27, 18.13, 17, 15.87, 14.73, 13.6, 12.47, 11.9, 11.33, 10.77, 10.2, 9.63, 9.07, 8.5, 7.93, 7.37, 6.8, 6.57, 6.35, 6.12, 5.89, 5.67, 5.44, 5.21, 4.99, 4.76, 4.53, 4.31, 4.08, 3.85, 3.63, 3.4, 3.29, 3.17, 3.06, 2.95, 2.83, 2.72, 2.61, 2.49, 2.38, 2.27, 2.15, 2.04, 1.93, 1.81, 1.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double majorfedexscores[] = {600, 330, 210, 150, 120, 110, 100, 94, 88, 82, 77, 72, 68, 64, 61, 59, 57, 55, 53, 51, 48.73, 46.47, 44.2, 41.93, 40.23, 38.53, 36.83, 35.13, 33.43, 31.73, 30.03, 28.33, 26.63, 24.93, 23.8, 22.67, 21.53, 20.4, 19.27, 18.13, 17, 15.87, 14.73, 13.6, 12.47, 11.9, 11.33, 10.77, 10.2, 9.63, 9.07, 8.5, 7.93, 7.37, 6.8, 6.57, 6.35, 6.12, 5.89, 5.67, 5.44, 5.21, 4.99, 4.76, 4.53, 4.31, 4.08, 3.85, 3.63, 3.4, 3.29, 3.17, 3.06, 2.95, 2.83, 2.72, 2.61, 2.49, 2.38, 2.27, 2.15, 2.04, 1.93, 1.81, 1.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double playoffscores[] = {2000, 1200, 760, 540, 440, 400, 360, 340, 320, 300, 280, 260, 240, 228, 220, 212, 204, 196, 188, 180, 172, 164, 156, 148, 142, 136, 130, 124, 118, 112, 106, 100, 94, 88, 84, 80, 76, 72, 68, 64, 60, 56, 52, 48, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 23.2, 22.4, 21.6, 20.8, 20, 19.2, 18.4, 17.6, 16.8, 16, 15.2, 14.4, 13.6, 12.8, 12, 11.6, 11.2, 10.8, 10.4, 10, 9.6, 9.2, 8.8, 8.4, 8, 7.6, 7.2, 6.8, 6.4, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	srand(time(NULL));

	for (int i = 0; i < golfernum; i++) {
		golfers[i].fedexpoints = 0;
	}
	
	for (int i = 0; i < numyears; i++) {
		
		for (int j = 0; j < 43; j++) {
			determine_winner(golfers, golfernum, j, regulartourneyscores, wgcfedexscores, majorfedexscores, playoffscores, tourneyprintflag, i);
			shuffle(golfers, golfernum);
			for (int k = 0; k < golfernum; k++) {
				golfers[k].placedflag = false;
			}
		}

		fedex_sort(golfers, golfernum);
		cout << "FedEx Cup Leaderboard:\n";
		for (int i = 0; i < 10; i++) {
			cout << golfers[i].name << ": " << golfers[i].fedexpoints << "\n";
		}
		golfers[0].numfedexcupswon++;
		cout << "\n" << golfers[0].name << " wins the " << i + 2020 << " FedEx Cup!\n\n";

		for (int k = 0; k < golfernum; k++) {
			golfers[k].fedexpoints = 0;
		}
	}	

	sort(golfers, golfernum);
	cout << '\n' << "Here are the results of simulating a career for these golfers of " << numyears << " years: " << '\n' << '\n';

	for (int i = 0; i < golfernum; i++) {
		cout << golfers[i].name << ": " << golfers[i].pgatourwins << " PGA Tour events won, " << golfers[i].majorswon << " majors (" << golfers[i].masterswon << " Masters, " << golfers[i].pgaswon << " PGA Championships, " << golfers[i].usopenswon << " U.S. Opens, " << golfers[i].openswon << " Open Championships), " << golfers[i].numfedexcupswon << " FedEx Cups won." << '\n';
	}
	
}
