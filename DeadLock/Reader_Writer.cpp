#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t mutex, rw_mutex;
int read_count = 0;
int shared_data = 0;  // renamed shared resource

void* reader(void* arg) {
    int id = *((int*)arg);
    while (true) {

        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) 
            sem_wait(&rw_mutex); // First reader locks resource
        sem_post(&mutex);

        // Reading section
        cout << "Reader " << id << " reads shared_data = " << shared_data << endl;
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) 
            sem_post(&rw_mutex); // Last reader unlocks
        sem_post(&mutex);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (true) {
        sem_wait(&rw_mutex);

        // Writing section
        shared_data++;
        cout << "Writer " << id << " writes shared_data = " << shared_data << endl;
        sleep(1);

        sem_post(&rw_mutex);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t r1, r2, w1;
    int r_id1 = 1, r_id2 = 2, w_id = 1;

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    pthread_create(&r1, NULL, reader, &r_id1);
    pthread_create(&r2, NULL, reader, &r_id2);
    pthread_create(&w1, NULL, writer, &w_id);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    return 0;
}
