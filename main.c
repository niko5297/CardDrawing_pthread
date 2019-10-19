#include <stdio.h>
#include <string.h>
#include <mach/boolean.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

char hearts[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool heartsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char spades[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool spadesbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char clubs[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool clubsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char diamonds[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool diamondsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
    pthread_mutex_t pthread_draw, pthread_read, pthread_check, pthread_type;
int numberOfCardsLeft=56;


int drawCard(){
    int number;
    pthread_mutex_lock(&pthread_draw);
    // Current time as seed for random
    srand(time(0));
    printf("Selecting random cardnumber from pthread_draw...\n");
        number = rand()%13+1;
        sleep(1);
    pthread_mutex_unlock(&pthread_draw);
        return number;

}
int drawType(){
    int type;
    pthread_mutex_lock(&pthread_type);
    printf("Selecting random cardtype from pthread_draw...\n");
    type = rand()%4+1;
    sleep(1);
    pthread_mutex_unlock(&pthread_type);
    return type;

}

int checkCard(int type, int number){
    pthread_mutex_lock(&pthread_check);
    printf("Checking the card from pthread_check...\n");

    switch(type){
        case 1:
            if (heartsbool[number] == false){
                sleep(1);
                numberOfCardsLeft--;
                pthread_mutex_unlock(&pthread_check);
                return 1;
            }
            else
                sleep(1);
                pthread_mutex_unlock(&pthread_check);
                return 0;
        case 2:
            if (spadesbool[number] == false){
                sleep(1);
                numberOfCardsLeft--;
                pthread_mutex_unlock(&pthread_check);
                return 1;
            }
            else
                sleep(1);
                pthread_mutex_unlock(&pthread_check);
                return 0;
        case 3:
            if (clubsbool[number] == false){
                sleep(1);
                numberOfCardsLeft--;
                pthread_mutex_unlock(&pthread_check);
                return 1;
            }
            else
                sleep(1);
                pthread_mutex_unlock(&pthread_check);
                return 0;
        case 4:
            if (diamondsbool[number] == false){
                sleep(1);
                numberOfCardsLeft--;
                pthread_mutex_unlock(&pthread_check);
                return 1;
            }
            else
                sleep(1);
                pthread_mutex_unlock(&pthread_check);
                return 0;
    }
    pthread_mutex_unlock(&pthread_check);


}

void readCard(int type, int number){
    pthread_mutex_lock(&pthread_read);
    printf("Reading card from pthread_read...\n\n");


    if (type==1){
        printf("You have drawn %s of Hearts\n\n",hearts[number]);
        heartsbool[number] = true;

    }
    if (type==2){
        printf("You have drawn %s of Spades\n\n",spades[number]);
        spadesbool[number] = true;

    }
    if (type==3){
        printf("You have drawn %s of Clubs\n\n",clubs[number]);
        clubsbool[number] = true;

    }
    if (type==4){
        printf("You have drawn %s of Diamonds\n\n",diamonds[number]);
        diamondsbool[number] = true;

    }
    sleep(1);

    pthread_mutex_unlock(&pthread_read);

}




int main() {
    //TODO:
    /**
     * Find en måde hvorpå at der vises en introduktion før scanf.
     * Find bedre løsning til et kort der er blevet trukket.
     */

    /**
    * Læs op på pthread_mutex, da dette kun skal bruges som lås og IKKE thread.
    * Lav derfor nye threads i din main.
    * https://randu.org/tutorials/threads/
    * https://dev.to/quantumsheep/basics-of-multithreading-in-c-4pam
    */

    int cardNumber, cardType, hasTheCardBeenDrawn, numberOfCardsBeingDrawn;
    int firstTime = 0;

    pthread_mutex_init(&pthread_draw, NULL);
    pthread_mutex_init(&pthread_check, NULL);
    pthread_mutex_init(&pthread_read, NULL);
    pthread_mutex_init(&pthread_type, NULL);

    printf("This program lets you draw and read cards using multithreaded pthread_mutex\n");

    printf("How many cards do you want to draw?\n");

    while (scanf("%d", &numberOfCardsBeingDrawn)!=0) {
        srand(0);
        if (numberOfCardsLeft==0){
            printf("The game is over.... There is no more cards left\n");
            exit(0);
        }

        if (firstTime==1){
            printf("How many cards do you want to draw?\n");
        }
        firstTime=1;



        for (int i = 0; i < numberOfCardsBeingDrawn; ++i) {

            if (numberOfCardsLeft == 0){
                printf("The game is over.... There is no more cards left\n");
                exit(0);
            }

            cardType = drawType();
            cardNumber = drawCard();
            printf("%d", cardType);
            hasTheCardBeenDrawn = checkCard(cardType, cardNumber);

            do {
                if (hasTheCardBeenDrawn) {
                    readCard(cardType, cardNumber);
                    break;
                }
                printf("The selected card has been drawn before, drawing a new one\n\n");
                srand(0);
                cardType = drawType();
                cardNumber = drawCard();
                hasTheCardBeenDrawn = checkCard(cardType, cardNumber);
            } while (!hasTheCardBeenDrawn);
        }

            if (numberOfCardsLeft == 0){
                printf("The game is over.... There is no more cards left\n");
                exit(0);
            }








            /*for (int i = 0; i < 2; ++i) {
                printf("%d ", *(elementNumber+i));
            }
             */

            //read(elementNumber[]);

            //printf("%s",hearts[8]);
        }
    }