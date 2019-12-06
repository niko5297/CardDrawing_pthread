#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdbool.h>

#define MAX_CARDS 56

//Define global variables
char hearts[14][13] = {"Ace", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
bool heartsbool[14] = {false, false, false, false, false, false, false, false, false, false, false, false, false,
                       false};
char spades[14][13] = {"Ace", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
bool spadesbool[14] = {false, false, false, false, false, false, false, false, false, false, false, false, false,
                       false};
char clubs[14][13] = {"Ace", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
bool clubsbool[14] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false};

char diamonds[14][13] = {"Ace", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
bool diamondsbool[14] = {false, false, false, false, false, false, false, false, false, false, false, false, false,
                         false};

pthread_mutex_t mutex_read;
pthread_mutex_t mutex_number;
pthread_mutex_t mutex_type;
int numberOfCardsLeft = MAX_CARDS;
int numberOfHeartsLeft = 14;
int numberOfSpadesLeft = 14;
int numberOfClubsLeft = 14;
int numberOfDiamondsLeft = 14;
int numberOfCardsToBeDrawn;


/**
 * This method reads the given number and type of card
 * and then displays it for the user
 * @param number, the card number (King, 10, 5, etc.)
 * @param type, the type of card (hearts, spades etc.)
 * @return a print of the chosen card
 */

void *readCard(int number, int type) {
    switch (type) {
        case 1:
            pthread_mutex_lock(&mutex_read);
            if (heartsbool[number] == false) {
                heartsbool[number] = true;
                numberOfCardsLeft--;
                numberOfHeartsLeft--;
                printf("You have drawn %s of Hearts\n\n",
                       hearts[number]);
            } else {
                printf("Already removed, drawn %s of Hearts\n\n",
                       hearts[number]);
            }
            pthread_mutex_unlock(&mutex_read);

            // Sleep threads to see what happens
            sleep(1);
            break;
        case 2:
            pthread_mutex_lock(&mutex_read);
            if (spadesbool[number] == false) {
                spadesbool[number] = true;
                numberOfCardsLeft--;
                numberOfSpadesLeft--;
                printf("You have drawn %s of Spades\n\n",
                       spades[number]);
            } else {
                printf("Already removed, drawn %s of Spades\n\n",
                       spades[number]);
            }
            pthread_mutex_unlock(&mutex_read);

            // Sleep threads to see what happens
            sleep(1);
            break;
        case 3:
            pthread_mutex_lock(&mutex_read);
            if (clubsbool[number] == false) {
                clubsbool[number] = true;
                numberOfCardsLeft--;
                numberOfClubsLeft--;
                printf("You have drawn %s of Clubs\n\n",
                       clubs[number]);
            } else {
                printf("Already removed, drawn %s of Clubs\n\n",
                       clubs[number]);
            }
            pthread_mutex_unlock(&mutex_read);

            // Sleep threads to see what happens
            sleep(1);
            break;
        case 4:
            pthread_mutex_lock(&mutex_read);
            if (diamondsbool[number] == false) {
                diamondsbool[number] = true;
                numberOfCardsLeft--;
                numberOfDiamondsLeft--;
                printf("You have drawn %s of Diamonds\n\n",
                       diamonds[number]);
            } else {
                printf("Already removed, drawn %s of Diamonds\n\n",
                       diamonds[number]);
            }
            pthread_mutex_unlock(&mutex_read);

            // Sleep threads to see what happens
            sleep(1);
            break;
    }
}

/**
 * This method shows how multithreading card drawing game works.
 * The method draws a type and a card.
 * It calls a help method which displays the user the card.
 * @return the card which have been drawn or error, the card has already been drawn
 */
void *run() {
    pthread_mutex_lock(&mutex_number);
    int number = rand() % 13 + 1;
    pthread_mutex_unlock(&mutex_number);

    pthread_mutex_lock(&mutex_type);
    int type = rand() % 4 + 1;
    pthread_mutex_unlock(&mutex_type);

    printf("Checking the card from pthread_check...\n");

    // Sleep threads to see what happens
    sleep(1);
    readCard(number, type);

    // Exit threads
    pthread_exit(0);
}


int main() {
    //Initialize pthread_mutex;
    if (pthread_mutex_init(&mutex_read, NULL) != 0 &&
        pthread_mutex_init(&mutex_number, NULL) != 0 &&
        pthread_mutex_init(&mutex_type, NULL) != 0) {
        printf("Mutex init failed, closing program...\n");
        exit(0);
    }

    // Set the seed
    srand(time(0));

    printf("\nThis program lets you draw and read cards using multithreaded pthread_mutex\n\n");
    printf("Made by Nikolaj Wassmann - s185082\n\n");


    printf("How many cards do you want to draw?\n\nType 0 to exit\n\n");

    //Gets input from user to select how many cards that needs to be drawn
    scanf("%d", &numberOfCardsToBeDrawn);
    while (numberOfCardsToBeDrawn > 0 && numberOfCardsToBeDrawn <= MAX_CARDS) {

        if (numberOfCardsLeft == 0) {
            // If no cards left, exit
            printf("There are no more cards left. Closing program...\n");
            break;
        }

        int numberOfThreadsToJoin = numberOfCardsToBeDrawn;

        pthread_t threads[MAX_CARDS] = {};

        // Create all the number of threads equivalent to the cards being drawn
        for (int i = 0; i < numberOfCardsToBeDrawn; i++) {
            pthread_create(&(threads[i]), NULL, run, NULL);
        }

        // Join all the threads
        for (int i = 0; i < numberOfThreadsToJoin; i++) {
            pthread_join(threads[i], NULL);
        }

        printf("How many cards do you want to draw?\n\nType 0 to exit\n\n");
        scanf("%d", &numberOfCardsToBeDrawn);
        if (numberOfCardsLeft == 0) {
            // If no cards left, exit
            printf("There are no more cards left. Closing program...\n");
            break;
        }

    }

    //To prevent memory leak, destory mutex
    pthread_mutex_destroy(&mutex_read);
    pthread_mutex_destroy(&mutex_number);
    pthread_mutex_destroy(&mutex_type);
}
