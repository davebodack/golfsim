#ifndef GOLFSIM_H
#define GOLFSIM_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <math.h>

#include "Player.h"

using namespace std;

Player determine_winner(Player golfers[], int golfernum, int major);
bool determine_match_winner(Player golfer1, Player golfer2);
int determine_hole_winner(Player golfer1, Player golfer2);
int determine_foursome_winner(Player golfer1, Player golfer2, Player golfer3, Player golfer4);
void print_hole_details(Player winninggolfer, Player losinggolfer, bool tieflag);
Player* run_match(Player golfer1, Player golfer2, int nummatches, bool detailsflag);

double sum(Player golfers[], int golfernum);
void shuffle(Player golfers[], int golferssize);
void swap(Player& x, Player& y);
void sort(Player golfers[], int golfernum);
void match_sort(Player golfers[], int golfernum);
void ryder_cup_sort(Player golfers[]);
void draft_sort(Player golfers[]);

#endif