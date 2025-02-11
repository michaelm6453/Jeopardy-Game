/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, < Michael Morra, Saieason Sritharan, Cam Edwards, Destiny Mekwunye>
 * All rights reserved.
 *
 */
 
#define RESET "\x1B[0m"
#define ORANGE "\x1B[38;5;208m"
#define BLUE "\x1B[34m"
#ifndef JEOPARDY_H_
#define JEOPARDY_H_

#define MAX_LEN 256

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.

void tokenize(char *input, char *answer);

// Displays the game results for each player, their name and final score, ranked from first to last place

void show_results(player *players, int num_players);
void initialize_game(void);

#endif /* JEOPARDY_H_ */
