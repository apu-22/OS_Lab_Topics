#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t sem_even;
sem_t sem_odd;

int num = 0;  

void* printEven(void* arg) {
    while (num <= 10) {

        sem_wait(&sem_even);  // even thread -->turn

        if (num > 10) {
            sem_post(&sem_odd);
            break;
        }

        if (num % 2 == 0) {
            cout << "Even: " << num << endl;
            num++;
        }

        sleep(1);  // even thread delay

        sem_post(&sem_odd);  // odd thread -->start
    }
    return NULL;
}

void* printOdd(void* arg) {
    while (num <= 10) {

        sem_wait(&sem_odd);  // odd thread--> turn

        if (num > 10) {
            sem_post(&sem_even);
            break;
        }

        if (num % 2 == 1) {
            cout << "Odd:  " << num << endl;
            num++;
        }

        sleep(2);  // odd thread delay

        sem_post(&sem_even);  // even thread--> allow
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&sem_even, 0, 1); // even print first (0)
    sem_init(&sem_odd,  0, 0); // odd can not print first

    pthread_create(&t1, NULL, printEven, NULL);
    pthread_create(&t2, NULL, printOdd,  NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem_even);
    sem_destroy(&sem_odd);

    return 0;
}
