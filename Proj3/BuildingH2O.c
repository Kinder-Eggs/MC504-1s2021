#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t mutex;
int oxygen = 0;
int hydrogen = 0;
pthread_barrier_t barrier;
sem_t oxyQueue;
sem_t hydroQueue;
sem_t action;

void* oxygenThread(void* v);
void* hydrogenThread(void* v);
void bond();
void print();


int main() {
    // Initializes variables, semaphores and barrier
    pthread_t thr[99];
    sem_init(&mutex, 0, 1);
    sem_init(&action, 0, 1);
    sem_init(&oxyQueue, 0, 0);
    sem_init(&hydroQueue, 0, 0);
    pthread_barrier_init(&barrier, NULL, 3); 
    time_t t;
    srand((unsigned) time(&t));
    int ocounter = 0, hcounter = 0;

    print();
    // Indefinitely generates oxygen and hydrogen threads
    // Keeps a balance of 33 Oxygens and 66 Hydrogens every 99 threads
    while(1){
        for(int i = 0; i < 99; i++) {
            if((rand()%3 && hcounter < 67) || ocounter == 33) {
                pthread_create(&thr[i], NULL, hydrogenThread, NULL);
                hcounter++;
            }
            else {
                pthread_create(&thr[i], NULL, oxygenThread, NULL);
            }
        }
        for(int i = 0; i < 99; i++)
            pthread_join(thr[i], NULL);
    }
}


void* oxygenThread(void* v) {
    sem_wait(&mutex);  // Grabs the mutex lock
    oxygen++;
    print();
    if(hydrogen >= 2) {  // If there is enough to make water
        sem_post(&hydroQueue);
        sem_post(&hydroQueue);
        hydrogen -= 2;
        sem_post(&oxyQueue);
        oxygen--;
    } else
        sem_post(&mutex);  // Else releases mutex lock
    
    sem_wait(&oxyQueue);
    bond();
    
    pthread_barrier_wait(&barrier);
    sem_post(&mutex);

    return NULL;
}


void* hydrogenThread(void* v) {
    sem_wait(&mutex);
    hydrogen++;
    print();
    if(hydrogen >= 2 && oxygen >= 1) {
        sem_post(&hydroQueue);
        sem_post(&hydroQueue);
        hydrogen -= 2;
        sem_post(&oxyQueue);
        oxygen -= 1;
    } else
        sem_post(&mutex);

    sem_wait(&hydroQueue);
    
    pthread_barrier_wait(&barrier);
    sem_post(&action);

    return NULL;
}


void print() {
    system("clear");
    if(oxygen > 0)
        printf("                     ___\nOxygens: %d   |      /   \\\n             |      | O |\n             |      \\___/\n             |", oxygen);
    else
        printf("\nOxygens: %d   |\n             |\n             |\n             |", oxygen);
    if(hydrogen == 1)
        printf("\n             |\n             |\n             |   ___\n             |  /   \\\n             |  | H |\nHydrogens: %d |  \\___/\n", hydrogen);
    else if(hydrogen > 1)
        printf("\n             |\n             |\n             |   ___     ___\n             |  /   \\   /   \\\n             |  | H |   | H |\nHydrogens: %d |  \\___/   \\___/\n", hydrogen);
    else
        printf("\n             |\n             |\n             |\n             |\n             |\nHydrogens: %d |\n", hydrogen);
    usleep(500000);
}


void bond() {
    system("clear");
    printf("                     ___\nOxygens: %d   |      /   \\\n             |      | O |\n             |      \\___/\n             |       / \\", oxygen);
    printf("\n             |      /   \\\n             |     /     \\\n             |   _┴_     _┴_\n             |  /   \\   /   \\\n             |  | H |   | H |\nHydrogens: %d |  \\___/   \\___/\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                      ___\nOxygens: %d   |       /   \\\n             |       | O |\n             |       \\___/\n             |        / \\", oxygen);
    printf("\n             |       /   \\\n             |      /     \\\n             |    _┴_     _┴_\n             |   /   \\   /   \\\n             |   | H |   | H |\nHydrogens: %d |   \\___/   \\___/\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                       ___\nOxygens: %d   |        /   \\\n             |        | O |\n             |        \\___/\n             |         / \\", oxygen);
    printf("\n             |        /   \\\n             |       /     \\\n             |     _┴_     _┴_\n             |    /   \\   /   \\\n             |    | H |   | H |\nHydrogens: %d |    \\___/   \\___/\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                        ___\nOxygens: %d   |         /   \\\n             |         | O |\n             |         \\___/\n             |          / \\", oxygen);
    printf("\n             |         /   \\\n             |        /     \\\n             |      _┴_     _┴_\n             |     /   \\   /   \\\n             |     | H |   | H |\nHydrogens: %d |     \\___/   \\___/\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                         ___\nOxygens: %d   |          /   \\\n             |          | O |\n             |          \\___/\n             |           / \\", oxygen);
    printf("\n             |          /   \\\n             |         /     \\\n             |       _┴_     _┴_\n             |      /   \\   /   \\\n             |      | H |   | H |\nHydrogens: %d |      \\___/   \\___/\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                          ___\nOxygens: %d   |           /   \\\n             |           | O |\n             |           \\___/\n             |            / \\", oxygen);
    printf("\n             |           /   \\\n             |          /     \\\n             |        _┴_     _┴_\n             |       /   \\   /   \\\n             |       | H |   | H |\nHydrogens: %d |       \\___/   \\___/\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                           ___\nOxygens: %d   |            /   \\\n             |            | O |\n             |            \\___/\n             |             / \\", oxygen);
    printf("\n             |            /   \\\n             |           /     \\\n             |         _┴_     _┴_\n             |        /   \\   /   \\\n             |        | H |   | H |\nHydrogens: %d |        \\___/   \\___/\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                            ___\nOxygens: %d   |             /   \\\n             |             | O |\n             |             \\___/\n             |              / \\", oxygen);
    printf("\n             |             /   \\\n             |            /     \\\n             |          _┴_     _┴_\n             |         /   \\   /   \n             |         | H |   | H \nHydrogens: %d |         \\___/   \\___\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                             ___\nOxygens: %d   |              /   \\\n             |              | O |\n             |              \\___/\n             |               / \\", oxygen);
    printf("\n             |              /   \\\n             |             /     \\\n             |           _┴_     _┴\n             |          /   \\   /   \n             |          | H |   | H\nHydrogens: %d |          \\___/   \\__\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                              ___\nOxygens: %d   |               /   \\\n             |               | O |\n             |               \\___/\n             |                / \\", oxygen);
    printf("\n             |               /   \\\n             |              /     \\\n             |            _┴_     _\n             |           /   \\   /   \n             |           | H |   | \nHydrogens: %d |           \\___/   \\_\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                               ___\nOxygens: %d   |                /   \\\n             |                | O |\n             |                \\___/\n             |                 / \\", oxygen);
    printf("\n             |                /   \\\n             |               /     \n             |             _┴_     \n             |            /   \\   /   \n             |            | H |   |\nHydrogens: %d |            \\___/   \\\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                                ___\nOxygens: %d   |                 /   \n             |                 | O \n             |                 \\___\n             |                  / \\", oxygen);
    printf("\n             |                 /   \n             |                /     \n             |              _┴_     \n             |             /   \\      \n             |             | H |   \nHydrogens: %d |             \\___/   \n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                                 __\nOxygens: %d   |                  /   \n             |                  | O\n             |                  \\__\n             |                   / ", oxygen);
    printf("\n             |                  /   \n             |                 /     \n             |               _┴_     \n             |              /   \\      \n             |              | H |   \nHydrogens: %d |              \\___/   \n", hydrogen);
    usleep(200000);
    system("clear");
    printf("                                  _\nOxygens: %d   |                   /   \n             |                   | \n             |                   \\_\n             |                    / ", oxygen);
    printf("\n             |                   /   \n             |                  /     \n             |                _┴_     \n             |               /   \\      \n             |               | H |   \nHydrogens: %d |               \\___/   \n", hydrogen);
    usleep(200000);
    system("clear");
    printf("\nOxygens: %d   |                    /\n             |                    |\n             |                    \\\n             |", oxygen);
    printf("\n             |                    /   \n             |                   /     \n             |                 _┴_     \n             |                /   \\      \n             |                | H |   \nHydrogens: %d |                \\___/   \n", hydrogen);
    usleep(200000);
    system("clear");
    printf("\nOxygens: %d   |\n             |\n             |\n             |", oxygen);
    printf("\n             |\n             |                   /     \n             |                 _┴_     \n             |                /\n             |                | H\nHydrogens: %d |                \\___\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("\nOxygens: %d   |\n             |\n             |\n             |", oxygen);
    printf("\n             |\n             |\n             |                  _┴\n             |                 /\n             |                 | H\nHydrogens: %d |                 \\__\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("\nOxygens: %d   |\n             |\n             |\n             |", oxygen);
    printf("\n             |\n             |\n             |                   _\n             |                  /\n             |                  |\nHydrogens: %d |                  \\_\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("\nOxygens: %d   |\n             |\n             |\n             |", oxygen);
    printf("\n             |\n             |\n             |\n             |                   /\n             |                   |\nHydrogens: %d |                   \\\n", hydrogen);
    usleep(200000);
    system("clear");
    printf("\nOxygens: %d   |\n             |\n             |\n             |", oxygen);
    printf("\n             |\n             |\n             |\n             |\n             |\nHydrogens: %d |\n", hydrogen);
    
    usleep(50000);
    print();
}   
