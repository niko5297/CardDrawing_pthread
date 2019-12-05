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
void* run(void* bag) {
    int random;
    pthread_mutex_lock(&mutex_ran_number);
    random = rand(); //I think the seed is shared ahh
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
                printf("Card left before: %d\n",numberOfCardsLeft);
                numberOfCardsLeft--;
                //cardsLeft--;
                numberOfHeartsLeft--;
                printf("You have drawn %s of Hearts, thread \n\n",
                       hearts[number]);
                printf("Card left after: %d\n",numberOfCardsLeft);
                pthread_mutex_unlock(&mutex);
            }else{
                printf("Already removed, drawn %s of Hearts, thread \n\n",
                       hearts[number]);
                pthread_mutex_unlock(&mutex);
            }
            sleep(1);
            break;
        case 2:
            pthread_mutex_lock(&mutex);
            if (spadesbool[number] == false) {
                spadesbool[number] = true;
                printf("Card left before: %d\n",numberOfCardsLeft);
                numberOfCardsLeft--;
                //cardsLeft--;
                numberOfSpadesLeft--;
                printf("You have drawn %s of Spades, thread \n\n",
                       spades[number]);
                printf("Card left after: %d\n",numberOfCardsLeft);
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
                printf("Card left before: %d\n",numberOfCardsLeft);
                numberOfCardsLeft--;
                //cardsLeft--;
                numberOfClubsLeft--;
                printf("You have drawn %s of Clubs, thread \n\n",
                       clubs[number]);
                printf("Card left after: %d\n",numberOfCardsLeft);
                pthread_mutex_unlock(&mutex);
            }else{
                printf("Already removed, drawn %s of Clubs, thread \n\n",
                       clubs[number]);
                pthread_mutex_unlock(&mutex);
            }
            sleep(1);
            break;
        case 4:
            pthread_mutex_lock(&mutex);
            if (diamondsbool[number] == false) {
                diamondsbool[number] = true;
                printf("Card left before: %d\n",numberOfCardsLeft);
                numberOfCardsLeft--;
                //cardsLeft--;
                numberOfDiamondsLeft--;
                printf("You have drawn %s of Diamonds, thread \n\n",
                       diamonds[number]);
                printf("Card left after: %d\n",numberOfCardsLeft);
                pthread_mutex_unlock(&mutex);
            }else{
                printf("Already removed, drawn %s of Diamonds, thread\n\n",
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
        printf("\n mutex init failed\n");
        return 1;
    }

    // Set the seed
    srand(time(0));

    printf("\nThis program lets you draw and read cards using multithreaded pthread_mutex\n\n");
    printf("Made by Nikolaj Wassmann - s185082\n\n");


    printf("How many cards do you want to draw?\n\nType 0 to exit\n\n");
    //Gets input from user to select how many cards that needs to be drawn
    scanf("%d", &cardsLeft);
    while (cardsLeft > 0 && cardsLeft <= MAX_CARDS || numberOfCardsLeft!=0)
    {
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
        //you have to reinitialize the shared variables here if you want to start from the begining
        //cant remember what your game wanted here so its left for you to decide
        printf("How many cards do you want to draw?\n\nType 0 to exit\n\n2");
        //printf("%d",numberOfCardsLeft);
        scanf("%d", &cardsLeft);

    }
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex_ran_number);
    pthread_mutex_destroy(&mutex_ran_type);
}
