/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, Michael Morra, Saieason Sritharan, Cam Edwards, Destiny Mekwunye


 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "questions.h"

question questions[NUM_QUESTIONS];

char categories[NUM_CATEGORIES][MAX_LEN] = {
    "programming",
    "algorithms",
    "databases"
};

// Initializes the array of questions for the game
void initialize_game(void)
{
    memset(questions, 0, sizeof(questions));

    questions[0] = (question){"programming", "Which language is known as the mother of all programming languages?", "C", 100, false};
    questions[1] = (question){"programming", "Which programming paradigm is based on the concept of objects?", "Object-oriented programming", 200, false};
    questions[2] = (question){"programming", "What does IDE stand for in software development?", "Integrated Development Environment", 300, false};
    questions[3] = (question){"programming", "Which company developed the Java programming language?", "Sun Microsystems", 400, false};

    questions[4] = (question){"algorithms", "Which algorithm is commonly used for searching in a sorted array?", "Binary search", 100, false};
    questions[5] = (question){"algorithms", "Which sorting algorithm has an average time complexity of O(n log n)?", "Merge sort", 200, false};
    questions[6] = (question){"algorithms", "What is the name of the algorithm used to find the shortest path in a weighted graph?", "Dijkstra's algorithm", 300, false};
    questions[7] = (question){"algorithms", "Which algorithm is used for finding the minimum spanning tree of a graph?", "Kruskal's algorithm", 400, false};

    questions[8] = (question){"databases", "What does SQL stand for?", "Structured Query Language", 100, false};
    questions[9] = (question){"databases", "Which type of database is based on tables, rows, and columns?", "Relational database", 200, false};
    questions[10] = (question){"databases", "Which type of database does not require a fixed schema?", "NoSQL", 300, false};
    questions[11] = (question){"databases", "What is the process of ensuring data consistency across transactions called?", "ACID compliance", 400, false};
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void) {
    printf("These are the list of questions left to answer:\n");

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        int has_questions = 0;
        for (int j = 0; j < NUM_QUESTIONS; j++) {
            if (strcmp(questions[j].category, categories[i]) == 0 && !questions[j].answered) {
                if (!has_questions) {
                    printf("%s:\n", categories[i]);
                    has_questions = 1;
                }
                printf("   $%d -> %s\n", questions[j].value, questions[j].question);
            }
        }
        if (has_questions) {
            printf("\n");
        }
    }
}


// Displays the question for the category and dollar value
void display_question(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; ++i) {
        if (questions[i].value == value && strcmp(questions[i].category, category) == 0) {
            printf("For $%d: %s\n", questions[i].value, questions[i].question);
            return;
        }
    }
    printf("No question found for category '%s' with value $%d.\n", category, value);
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for (int i = 0; i < NUM_QUESTIONS; ++i)
    {
        if (questions[i].value == value && strcmp(questions[i].category, category) == 0)
        {
            return strcasecmp(questions[i].answer, answer) == 0;
        }
    }
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value) {
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (questions[i].value == value && strcmp(questions[i].category, category) == 0) {
            return questions[i].answered;
        }
    }
    return true;
}
