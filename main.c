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
    pthread_mutex_t pthread_draw, pthread_read, pthread_check;
    /**
     * Læs op på pthread_mutex, da dette kun skal bruges som lås og IKKE thread.
     * Lav derfor nye threads i din main.
     * https://randu.org/tutorials/threads/
     * https://dev.to/quantumsheep/basics-of-multithreading-in-c-4pam
     * @return
     */


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
    pthread_mutex_lock(&pthread_draw);
    // Current time as seed for random
    srand(time(0));
    printf("Selecting random cardtype from pthread_draw...\n");
    type = rand()%4+1;
    sleep(1);
    pthread_mutex_unlock(&pthread_draw);
    return type;

}

int checkCard(int type, int number){
    pthread_mutex_lock(&pthread_check);
    printf("Checking the card from pthread_check...\n");

    switch(type){
        case 1:
            if (heartsbool[number] == false){
                sleep(1);
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
    printf("Reading card from pthread_read...\n");


    if (type==1){
        printf("You have drawn %s of Hearts\n",hearts[number]);
        heartsbool[number] = true;

    }
    if (type==2){
        printf("You have drawn %s of Spades\n",spades[number]);
        spadesbool[number] = true;

    }
    if (type==3){
        printf("You have drawn %s of Clubs\n",clubs[number]);
        clubsbool[number] = true;

    }
    if (type==4){
        printf("You have drawn %s of Diamonds\n",diamonds[number]);
        diamondsbool[number] = true;

    }
    sleep(1);

    pthread_mutex_unlock(&pthread_read);

}




int main() {


    pthread_mutex_init(&pthread_draw,NULL);
    pthread_mutex_init(&pthread_check,NULL);
    pthread_mutex_init(&pthread_read,NULL);





    int cardNumber, cardType, hasTheCardBeenDrawn;

    cardType = drawType();
    cardNumber = drawCard();
    hasTheCardBeenDrawn = checkCard(cardType,cardNumber);

    printf("%d %d\n",cardNumber,cardType);

   // printf("%d",checkCard(1,1));

   if (hasTheCardBeenDrawn){
        readCard(cardType,cardNumber);
    }








    /*for (int i = 0; i < 2; ++i) {
        printf("%d ", *(elementNumber+i));
    }
     */

    //read(elementNumber[]);

    //printf("%s",hearts[8]);
}