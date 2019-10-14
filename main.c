#include <stdio.h>
#include <string.h>
#include <mach/boolean.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

char hearts[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool heartsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char spades[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool spadesbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char clubs[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool clubsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char diamonds[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool diamondsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
    pthread_mutex_t pthread_draw, pthread_read;
    /**
     * Læs op på pthread_mutex, da dette kun skal bruges som lås og IKKE thread.
     * Lav derfor nye threads i din main.
     * https://randu.org/tutorials/threads/
     * https://dev.to/quantumsheep/basics-of-multithreading-in-c-4pam
     * @return
     */


int draw(){
    int d;
    pthread_mutex_lock(&pthread_draw);
    // Current time as seed for random
    srand(time(0));
    printf("Drawing card using pthread_draw...\n");
        d = rand()%13+1;
        //printf("%d ",d);
    pthread_mutex_unlock(&pthread_draw);
    return d;
}

void read(int arg){
    pthread_mutex_lock(&pthread_read);
    printf("Reading card using pthread_read...\n");
    printf("%s", hearts[arg]);
    pthread_mutex_unlock(&pthread_read);

}




int main() {
    /**
     * Læs op på pthread_join
     */
    pthread_mutex_init(&pthread_draw,NULL);
    pthread_mutex_init(&pthread_read,NULL);


    int elementNumber = draw();
    read(elementNumber);

    //printf("%s",hearts[8]);
}