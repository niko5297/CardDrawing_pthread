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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_ran_number = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_ran_type = PTHREAD_MUTEX_INITIALIZER;
int numberOfCardsLeft = MAX_CARDS;
int numberOfHeartsLeft = 14;
int numberOfSpadesLeft = 14;
int numberOfClubsLeft = 14;
int numberOfDiamondsLeft = 14;
int cardsLeft;

/**
 *
 * @param bag
 * @return
 */
void* run() {
    int random;
    pthread_mutex_lock(&mutex_ran_number);
    random = rand();
    pthread_mutex_unlock(&mutex_ran_number);
    int number = random % 13 + 1;

    pthread_mutex_lock(&mutex_ran_type);
    random = rand();
    pthread_mutex_unlock(&mutex_ran_type);
    int type = random % 4 + 1;

    printf("Checking the card from pthread_check...\n");

    sleep(1);
    switch (type) {
        case 1:
            pthread_mutex_lock(&mutex);
            if (heartsbool[number] == false) {
                heartsbool[number] = true;
                numberOfCardsLeft--;
                numberOfHeartsLeft--;
                printf("You have drawn %s of Hearts\n\n",
                       hearts[number]);
                pthread_mutex_unlock(&mutex);
            }else{
                printf("Already removed, drawn %s of Hearts\n\n",
                       hearts[number]);
                pthread_mutex_unlock(&mutex);
            }
            sleep(1);
            break;
        case 2:
            pthread_mutex_lock(&mutex);
            if (spadesbool[number] == false) {
                spadesbool[number] = true;
                numberOfCardsLeft--;
                numberOfSpadesLeft--;
                printf("You have drawn %s of Spades\n\n",
                       spades[number]);
                pthread_mutex_unlock(&mutex);
            }else{
                printf("Already removed, drawn %s of Spades\n\n",
                       spades[number]);
                pthread_mutex_unlock(&mutex);
            }
            sleep(1);
            break;
        case 3:
            pthread_mutex_lock(&mutex);
            if (clubsbool[number] == false) {
                clubsbool[number] = true;
                numberOfCardsLeft--;
                numberOfClubsLeft--;
                printf("You have drawn %s of Clubs\n\n",
                       clubs[number]);
                pthread_mutex_unlock(&mutex);
            }else{
                printf("Already removed, drawn %s of Clubs\n\n",
                       clubs[number]);
                pthread_mutex_unlock(&mutex);
            }
            sleep(1);
            break;
        case 4:
            pthread_mutex_lock(&mutex);
            if (diamondsbool[number] == false) {
                diamondsbool[number] = true;
                numberOfCardsLeft--;
                numberOfDiamondsLeft--;
                printf("You have drawn %s of Diamonds\n\n",
                       diamonds[number]);
                pthread_mutex_unlock(&mutex);
            }else{
                printf("Already removed, drawn %s of Diamonds\n\n",
                       diamonds[number]);
                pthread_mutex_unlock(&mutex);
            }
            sleep(1);
            break;
    }
    pthread_exit(0);
}


int main() {
    //Initialize pthread_mutex;
    if (pthread_mutex_init(&mutex, NULL) != 0 &&
        pthread_mutex_init(&mutex_ran_number, NULL) != 0 &&
        pthread_mutex_init(&mutex_ran_type, NULL) != 0){
        printf("Mutex init failed, closing program...\n");
        exit(0);
    }

    // Set the seed
    srand(time(0));

    printf("\nThis program lets you draw and read cards using multithreaded pthread_mutex\n\n");
    printf("Made by Nikolaj Wassmann - s185082\n\n");


    printf("How many cards do you want to draw?\n\nType 0 to exit\n\n");

    //Gets input from user to select how many cards that needs to be drawn
    scanf("%d", &cardsLeft);
    while (cardsLeft > 0 && cardsLeft <= MAX_CARDS)
    {

        if (numberOfCardsLeft==0){
            // If no cards left, exit
            printf("There are no more cards left. Closing program...\n");
            break;
        }

        int countJoin = cardsLeft;

        pthread_t threads[MAX_CARDS] = {};
        for (int i=0;i<cardsLeft;i++)
        {
            pthread_create(&(threads[i]),NULL,run,NULL);
        }
        for (int i=0;i<countJoin;i++)
        {
            pthread_join(threads[i],NULL);
        }

        printf("How many cards do you want to draw?\n\nType 0 to exit\n\n");
        scanf("%d", &cardsLeft);
        if (numberOfCardsLeft==0){
            // If no cards left, exit
            printf("There are no more cards left. Closing program...\n");
            break;
        }

    }

    //To prevent memory leak, destory mutex
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex_ran_number);
    pthread_mutex_destroy(&mutex_ran_type);
}
