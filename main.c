#include <stdio.h>
#include <string.h>
#include <mach/boolean.h>
#include <stdbool.h>
#include <pthread.h>

char hearts[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool heartsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char spades[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool spadesbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char clubs[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool clubsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};
char diamonds[14][13] = {"Ace","1","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
bool diamondsbool[14] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false};



void *draw(void *arg){

}

void *read(void *arg){

}




int main() {
    /**
     * Læs op på pthread_join
     */
    pthread_t pthread_draw, pthread_read;
    pthread_create(&pthread_draw,NULL,draw, (void*)&pthread_draw);
    pthread_create(&pthread_read,NULL,read, (void*)&pthread_read);




    printf("%c",hearts[12][0]);
}