/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    char *delim = " ";
    char *word = strtok(input, delim);
    int index = 0;

    while (word != NULL) {
        tokens[index++] = word;
        word = strtok(NULL, delim);
    }

    tokens[index] = NULL;
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players) {
    // Sort players based on score
    for (int i = 0; i < NUM_PLAYERS - 1; i++) {
        for (int j = 0; j < NUM_PLAYERS - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    // Display results
    printf("\nFinal Scores:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%d. %s - $%d\n", i + 1, players[i].name, players[i].score);
    }
}

int main() {
    player players[NUM_PLAYERS];
    char buffer[BUFFER_LEN];
    char category[MAX_LEN];
    int value;
    
    // Initialize the game
    initialize_game();

    // Get player names
    printf("Enter player names:\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = '\0';
        players[i].score = 0;
    }

    // Game loop
    while (true) {
        // Display available categories
        display_categories();

        // Ask player to choose a category and value
        printf("Enter player's name: ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (!player_exists(players, NUM_PLAYERS, buffer)) {
            printf("Invalid player name. Try again.\n");
            continue;
        }

        printf("Choose a category: ");
        fgets(category, MAX_LEN, stdin);
        category[strcspn(category, "\n")] = '\0';

        printf("Choose a value: ");
        scanf("%d", &value);
        getchar(); // Consume newline

        // Validate if question is already answered
        if (already_answered(category, value)) {
            printf("This question has already been answered. Pick another one.\n");
            continue;
        }

        // Display the question
        display_question(category, value);
        printf("Enter your answer: ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Validate answer
        char *tokens[10];
        tokenize(buffer, tokens);
        
        if (tokens[0] == NULL || (strcmp(tokens[0], "what") != 0 && strcmp(tokens[0], "who") != 0)) {
            printf("Invalid format. Answers must start with 'what is' or 'who is'.\n");
            continue;
        }

        // Check correctness
        if (valid_answer(category, value, tokens[2])) {
            printf("Correct!\n");
            update_score(players, NUM_PLAYERS, buffer, value);
        } else {
            printf("Incorrect. The correct answer was: %s\n", questions[value / 100 - 1].answer);
        }

        // Mark question as answered
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
                questions[i].answered = true;
            }
        }

        // Check if game is over
        bool allAnswered = true;
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (!questions[i].answered) {
                allAnswered = false;
                break;
            }
        }
        if (allAnswered) break;
    }

    // Show final results
    show_results(players);
    return EXIT_SUCCESS;
}
