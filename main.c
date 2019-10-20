#include <stdio.h>
#include <string.h>
#include <mach/boolean.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

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

pthread_mutex_t pthread_draw, pthread_read, pthread_check, pthread_type;
int numberOfCardsLeft = 56, numberOfHeartsLeft = 14, numberOfSpadesLeft = 14, numberOfClubsLeft = 14, numberOfDiamondsLeft = 14;

/**
 * Method which selects one random of 14 different cards
 * @return position in array of types.
 */
int drawCard() {
    int number;
    pthread_mutex_lock(&pthread_draw);
    // Current time as seed for random
    srand(time(0));
    printf("Selecting random cardnumber from pthread_draw...\n");
    number = rand() % 13 + 1;
    sleep(1);
    pthread_mutex_unlock(&pthread_draw);
    return number;

}

/**
 * Method which selects the type of card, which will be read.
 * @return card type as an integer.
 */
int drawType() {
    int type;
    pthread_mutex_lock(&pthread_type);
    printf("Selecting random cardtype from pthread_draw...\n");
    type = rand() % 4 + 1;
    sleep(1);
    pthread_mutex_unlock(&pthread_type);
    return type;

}

/**
 * This method check if the random drawn card is vaild, meaning that the card haven't been drawn.
 * @param card type.
 * @param card number.
 * @return 1 or 0 depending if the card has been drawn before.
 */
int checkCard(int type, int number) {
    pthread_mutex_lock(&pthread_check);
    printf("Checking the card from pthread_check...\n");

    switch (type) {
        case 1:
            if (heartsbool[number] == false) {
                sleep(1);
                numberOfCardsLeft--;
                numberOfHeartsLeft--;
                pthread_mutex_unlock(&pthread_check);
                return 1;
            } else
                sleep(1);
            pthread_mutex_unlock(&pthread_check);
            return 0;
        case 2:
            if (spadesbool[number] == false) {
                sleep(1);
                numberOfCardsLeft--;
                numberOfSpadesLeft--;
                pthread_mutex_unlock(&pthread_check);
                return 1;
            } else
                sleep(1);
            pthread_mutex_unlock(&pthread_check);
            return 0;
        case 3:
            if (clubsbool[number] == false) {
                sleep(1);
                numberOfCardsLeft--;
                numberOfClubsLeft--;
                pthread_mutex_unlock(&pthread_check);
                return 1;
            } else
                sleep(1);
            pthread_mutex_unlock(&pthread_check);
            return 0;
        case 4:
            if (diamondsbool[number] == false) {
                sleep(1);
                numberOfCardsLeft--;
                numberOfDiamondsLeft--;
                pthread_mutex_unlock(&pthread_check);
                return 1;
            } else
                sleep(1);
            pthread_mutex_unlock(&pthread_check);
            return 0;
    }
    pthread_mutex_unlock(&pthread_check);


}

/**
 * Reads the card that have been drawn, and prints it to the console.
 * @param card type.
 * @param card number.
 */
void readCard(int type, int number) {
    pthread_mutex_lock(&pthread_read);
    printf("Reading card from pthread_read...\n\n");


    if (type == 1) {
        printf("You have drawn %s of Hearts\n\n", hearts[number]);
        heartsbool[number] = true;

    }
    if (type == 2) {
        printf("You have drawn %s of Spades\n\n", spades[number]);
        spadesbool[number] = true;

    }
    if (type == 3) {
        printf("You have drawn %s of Clubs\n\n", clubs[number]);
        clubsbool[number] = true;

    }
    if (type == 4) {
        printf("You have drawn %s of Diamonds\n\n", diamonds[number]);
        diamondsbool[number] = true;

    }
    sleep(1);

    pthread_mutex_unlock(&pthread_read);

}


int main() {

    //Initialize variables
    int cardNumber, cardType, hasTheCardBeenDrawn, numberOfCardsBeingDrawn;

    //Initialize pthread_mutex
    pthread_mutex_init(&pthread_draw, NULL);
    pthread_mutex_init(&pthread_check, NULL);
    pthread_mutex_init(&pthread_read, NULL);
    pthread_mutex_init(&pthread_type, NULL);

    printf("This program lets you draw and read cards using multithreaded pthread_mutex\n");

    //Main loop
    while (1) {
        printf("How many cards do you want to draw?\nType 0 to exit\n");

        //Gets input from user to select how many cards that needs to be drawn
        while (scanf("%d", &numberOfCardsBeingDrawn) != 0) {
            // Current time as seed for random
            srand(0);

            //If there are no more cards left, the game ends.
            if (numberOfCardsLeft == 0) {
                printf("The game is over.... There is no more cards left\n");
                exit(0);
            }

            //Card drawing, checking and reading loop.
            for (int i = 0; i < numberOfCardsBeingDrawn; ++i) {

                //If there are no more cards left, the game ends.
                if (numberOfCardsLeft == 0) {
                    printf("The game is over.... There is no more cards left\n");
                    exit(0);
                }

                //Methods from drawing and checking the card being called.
                cardType = drawType();
                cardNumber = drawCard();
                hasTheCardBeenDrawn = checkCard(cardType, cardNumber);


                do {
                    //checkCard(cardType, cardNumber) returns integer. The condition will be checked here.
                    if (hasTheCardBeenDrawn) {
                        readCard(cardType, cardNumber);
                        break;
                    }
                    printf("The selected card has been drawn before, drawing a new one\n\n");

                    // Current time as seed for random to make sure the next card draw is also random.
                    srand(0);

                    //Methods from drawing and checking the card being called.
                    cardType = drawType();
                    cardNumber = drawCard();
                    hasTheCardBeenDrawn = checkCard(cardType, cardNumber);

                    //Keep drawing until a new card is drawn.
                } while (!hasTheCardBeenDrawn);
            }

            //If there are no more cards left, the game ends.
            if (numberOfCardsLeft == 0) {
                printf("The game is over.... There is no more cards left\n");
                exit(0);
            }
            //If 0 is entered, exit the program.
            if (numberOfCardsBeingDrawn == 0) {
                printf("Goodbye...\n");
                exit(0);
            }
            break;









            /*for (int i = 0; i < 2; ++i) {
                printf("%d ", *(elementNumber+i));
            }
             */

            //read(elementNumber[]);

            //printf("%s",hearts[8]);
        }
    }
}