#ifndef PLAYER_H
#define PLAYER_H

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

#endif