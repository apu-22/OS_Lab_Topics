#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int accountA = 500; // Initial balance of account A
int accountB = 0;   // Initial balance of account B

pthread_mutex_t lock1; // mutex for critical section

void* transfer(void* arg) {
    int amount = *((int*)arg);

    // Enter critical section
    pthread_mutex_lock(&lock1);

    if (accountA >= amount) {
        sleep(1); // simulate preemption
        accountA -= amount;
        accountB += amount;
    }

    cout << "Transfer " << amount << ": A=" << accountA
         << ", B=" << accountB << " (Total: " << accountA + accountB << ")" << endl;

    // Exit critical section
    pthread_mutex_unlock(&lock1);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int amount1 = 100, amount2 = 500;

    pthread_mutex_init(&lock1, NULL);

    pthread_create(&thread1, NULL, transfer, &amount1);
    pthread_create(&thread2, NULL, transfer, &amount2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock1);

    cout << "Final balances: A=" << accountA
         << ", B=" << accountB
         << " (Total: " << accountA + accountB << ")" << endl;

    return 0;
}
