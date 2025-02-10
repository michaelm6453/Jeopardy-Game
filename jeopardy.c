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

// Tokenizes user input to extract the actual answer after "what is" or "who is"
void tokenize(char *input, char *answer) {
    char *prefix1 = "what is ";
    char *prefix2 = "who is ";

    if (strncmp(input, prefix1, strlen(prefix1)) == 0) {
        strcpy(answer, input + strlen(prefix1));
    } else if (strncmp(input, prefix2, strlen(prefix2)) == 0) {
        strcpy(answer, input + strlen(prefix2));
    } else {
        strcpy(answer, ""); // Invalid input format
    }
}

// Displays the game results for each player, their name, and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    // Sort players based on score (Descending Order)
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = 0; j < num_players - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
    // Display results
    printf("\nFinal Scores:\n");
    for (int i = 0; i < num_players; i++) {
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
        if (scanf("%d", &value) != 1) {
            printf("Invalid value. Try again.\n");
            getchar(); // Consume leftover input
            continue;
        }
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

        // Extract the actual answer
        char answer[MAX_LEN];
        tokenize(buffer, answer);

        if (strlen(answer) == 0) {
            printf("Invalid format. Answers must start with 'what is' or 'who is'.\n");
            continue;
        }

        // Check correctness
        if (valid_answer(category, value, answer)) {
            printf("Correct!\n");
            update_score(players, NUM_PLAYERS, buffer, value);
        } else {
            // Find correct answer
            for (int i = 0; i < NUM_QUESTIONS; i++) {
                if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
                    printf("Incorrect. The correct answer was: %s\n", questions[i].answer);
                    break;
                }
            }
        }

        // Mark question as answered
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
                questions[i].answered = true;
                break;
            }
        }

        // Check if all questions have been answered
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
