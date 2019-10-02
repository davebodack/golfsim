//Adds together the ratings of golfers in an array and returns the sum
double sum(Player golfers[], int golfernum) {
	
	double sum = 0;

	for (int i = 0; i < golfernum; i++) {
		sum += golfers[i].rating;
	}
	return sum;
}


//Modification of above sum function for eliminating players that have already been placed in a tournament
double career_sum(Player golfers[], int golfernum) {
	
	double sum = 0;

	for (int i = 0; i < golfernum; i++) {
		if (golfers[i].placedflag == false) {
			sum += golfers[i].rating;
		}
	}
	return sum;
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


//Sorts an array of golfers based on the number of FedEx Cup points the golfers have accrued
void fedex_sort(Player golfers[], int golfernum) {

	for (int num = 1; num < golfernum; num++) {
		for (int i = 0; i < golfernum - num; i++) {
			if (golfers[i].fedexpoints < golfers[i+1].fedexpoints) {
				swap(golfers[i], golfers[i+1]);
			}
		}
	}
}