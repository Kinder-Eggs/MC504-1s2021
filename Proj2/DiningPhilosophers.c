#include "table.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t semFork[5];  // Semaphore for each fork usage
sem_t semTable;  // Semaphore for each action (helps visualization)

// Prints the table and waits 1 second
void print();

// Changes the philosopher phil_id to hungry
void getHungry(int phil_id);

// Gets the philosopher phil_id with 2 forks to eat
void eatFood(int phil_id);

// Gets the philosopher phil_id to grab his left fork
void grabLeftFork(int phil_id);

// Gets the philosopher phil_id to grab his right fork
void grabRightFork(int phil_id);

// Makes the philosopher phil_id to release his forks
void releaseForks(int phil_id);

// Main function for each philosopher
void* randPhil(void *v);


int main() {
    pthread_t thr[5];
    int i, phil_id[5];

    // Initializes semaphores
    sem_init(&semTable, 0, 1);
    for (i = 0; i < 5; i++) {
        sem_init(&semFork[i], 0, 1);
    }

    // Creates 5 philosophers
    for (i = 0; i < 5; i++) {
        phil_id[i] = i;
        pthread_create(&thr[i], NULL, randPhil, (void*) &phil_id[i]);
    }

    for (i = 0; i < 5; i++)
        pthread_join(thr[i], NULL);
}


void* randPhil(void *v) {
    int phil_id = *(int *) v;
    int i;
    time_t t;
    srand((unsigned) time(&t));

    while(1) {  // Repeats indefinitely
        // Gets Hungry 2 out of 3 times, waits 1 second if it fails
        if(rand()%3) {
            getHungry(phil_id);

            // if phil_id is odd philosopher is right-handed
            // else philosopher is left-handed
            if (phil_id % 2) {
                grabRightFork(phil_id);
                grabLeftFork(phil_id);
            } else {
                grabLeftFork(phil_id);
                grabRightFork(phil_id);
            }
            eatFood(phil_id);
            sleep(rand()%3 + 1);  // Takes from 1 to 3 seconds to eat
            releaseForks(phil_id);
        } else {
            sleep(1);
        }
    }

    return NULL;
}


void print() {
    system("clear");
    printf("%s\n", table);
    sleep(1);
}


void getHungry(int phil_id) {
    sem_wait(&semTable);

    // Finds where to write text "HUNGRY" depending on phil_id
    int aux;
    if(phil_id == 0)
        aux = 240;
    else if(phil_id == 1)
        aux = 1381;
    else if(phil_id == 2)
        aux = 1726;
    else if(phil_id == 3)
        aux = 1324;
    else if(phil_id == 4)
        aux = 199;
    table[aux] = ' ';
    table[aux+1] = 'H';
    table[aux+2] = 'U';
    table[aux+3] = 'N';
    table[aux+4] = 'G';
    table[aux+5] = 'R';
    table[aux+6] = 'Y';
    table[aux+7] = ' ';
    print();
    sem_post(&semTable);
}


void eatFood(int phil_id) {
    sem_wait(&semTable);

    // Finds where to write text "EATING" depending on phil_id
    int aux;
    if(phil_id == 0)
        aux = 240;
    else if(phil_id == 1)
        aux = 1381;
    else if(phil_id == 2)
        aux = 1726;
    else if(phil_id == 3)
        aux = 1324;
    else if(phil_id == 4)
        aux = 199;
    table[aux] = ' ';
    table[aux+1] = 'E';
    table[aux+2] = 'A';
    table[aux+3] = 'T';
    table[aux+4] = 'I';
    table[aux+5] = 'N';
    table[aux+6] = 'G';
    table[aux+7] = ' ';
    print();
    sem_post(&semTable);
}


void grabLeftFork(int phil_id) {
    int nfork = (phil_id + 1) % 5;
    sem_wait(&semFork[nfork]);
    sem_wait(&semTable);

    // Finds where to mark '|' and remove respective fork
    switch (phil_id) {
    case 0:
        table[239] = '|';

        table[783] = ' ';
        table[784] = ' ';
        table[785] = ' ';
        table[786] = ' ';
        table[787] = ' ';
        table[788] = ' ';
        table[789] = ' ';
        table[790] = ' ';
        break;
    case 1:
        table[1380] = '|';

        table[1091] = ' ';
        table[1153] = ' ';
        table[1222] = ' ';
        table[1294] = ' ';
        break;
    case 2:
        table[1725] = '|';

        table[1077] = ' ';
        table[1137] = ' ';
        table[1204] = ' ';
        table[1274] = ' ';
        break;
    case 3:
        table[1323] = '|';

        table[750] = ' ';
        table[751] = ' ';
        table[752] = ' ';
        table[753] = ' ';
        table[754] = ' ';
        table[755] = ' ';
        table[756] = ' ';
        table[757] = ' ';
        break;
    case 4:
        table[198] = '|';

        table[287] = ' ';
        table[350] = ' ';
        table[410] = ' ';
        table[466] = ' ';
        break;
    }
    print();
    sem_post(&semTable);
}


void grabRightFork(int phil_id) {
    sem_wait(&semFork[phil_id]);
    sem_wait(&semTable);

    // Finds where to mark '|' and remove respective fork
    switch (phil_id) {
    case 0:
        table[248] = '|';

        table[287] = ' ';
        table[350] = ' ';
        table[410] = ' ';
        table[466] = ' ';
        break;
    case 1:
        table[1389] = '|';

        table[783] = ' ';
        table[784] = ' ';
        table[785] = ' ';
        table[786] = ' ';
        table[787] = ' ';
        table[788] = ' ';
        table[789] = ' ';
        table[790] = ' ';
        break;
    case 2:
        table[1734] = '|';

        table[1091] = ' ';
        table[1153] = ' ';
        table[1222] = ' ';
        table[1294] = ' ';
        break;
    case 3:
        table[1332] = '|';

        table[1077] = ' ';
        table[1137] = ' ';
        table[1204] = ' ';
        table[1274] = ' ';
        break;
    case 4:
        table[207] = '|';

        table[750] = ' ';
        table[751] = ' ';
        table[752] = ' ';
        table[753] = ' ';
        table[754] = ' ';
        table[755] = ' ';
        table[756] = ' ';
        table[757] = ' ';
        break;
    }
    print();
    sem_post(&semTable);
}


void releaseForks(int phil_id) {
    int dir = (phil_id + 1) % 5;
    sem_wait(&semTable);
    sem_post(&semFork[dir]);
    sem_post(&semFork[phil_id]);
    int aux;


    // Removes '|' marks, finds where to write "THINKING" depending on phil id
    // Replaces forks images on the table
    switch (phil_id) {
    case 0:
        aux = 240;
        table[287] = '|';  // Right fork
        table[350] = '|';
        table[410] = '|';
        table[466] = '|';

        table[783] = '_';  // Left Fork
        table[784] = '_';
        table[785] = '_';
        table[786] = '_';
        table[787] = '_';
        table[788] = '_';
        table[789] = '_';
        table[790] = '_';
        break;
    case 1:
        aux = 1381;
        table[783] = '_';  // Right fork
        table[784] = '_';
        table[785] = '_';
        table[786] = '_';
        table[787] = '_';
        table[788] = '_';
        table[789] = '_';
        table[790] = '_';

        table[1091] = '\\';  // Left fork
        table[1153] = '\\';
        table[1222] = '\\';
        table[1294] = '\\';
        break;
    case 2:
        aux = 1726;
        table[1091] = '\\';  // Right fork
        table[1153] = '\\';
        table[1222] = '\\';
        table[1294] = '\\';

        table[1077] = '/';  // Left fork
        table[1137] = '/';
        table[1204] = '/';
        table[1274] = '/';
        break;
    case 3:
        aux = 1324;
        table[1077] = '/';  // Right fork
        table[1137] = '/';
        table[1204] = '/';
        table[1274] = '/';

        table[750] = '_';  // Left fork
        table[751] = '_';
        table[752] = '_';
        table[753] = '_';
        table[754] = '_';
        table[755] = '_';
        table[756] = '_';
        table[757] = '_';
        break;
    case 4:
        aux = 199;
        table[750] = '_';  // Right fork
        table[751] = '_';
        table[752] = '_';
        table[753] = '_';
        table[754] = '_';
        table[755] = '_';
        table[756] = '_';
        table[757] = '_';

        table[287] = '|';  // Left fork
        table[350] = '|';
        table[410] = '|';
        table[466] = '|';
        break;
    }
    table[aux-1] = ' ';
    table[aux] = 'T';
    table[aux+1] = 'H';
    table[aux+2] = 'I';
    table[aux+3] = 'N';
    table[aux+4] = 'K';
    table[aux+5] = 'I';
    table[aux+6] = 'N';
    table[aux+7] = 'G';
    table[aux+8] = ' ';
    print();
    sem_post(&semTable);
}
