/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, < Michael Morra, Saieason Sritharan, Cam Edwards, Destiny Mekwunye>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"

// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name) {
    for (int i = 0; i < num_players; ++i) {
        if (strcmp(players[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}


// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, int num_players, char *name, int score) {
    for (int i = 0; i < num_players; ++i) {
        if (strcmp(players[i].name, name) == 0) {
            printf("Updating score for: %s, adding %d points\n", players[i].name, score);
            players[i].score += score;
            printf("New score for %s: %d\n", players[i].name, players[i].score);
            return;
        }
    }
    printf("Error: Player %s not found\n", name);
}

