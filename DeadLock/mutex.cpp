
#include <bits/stdc++.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int available_tickets = 1;
int tickets_sold = 0;

pthread_mutex_t mutex_lock; // Mutex declaration

void* book_tickets(void* arg)
{
    pthread_mutex_lock(&mutex_lock);   // Lock before entering critical section

    if (available_tickets > 0)
    {
        int current_tickets = available_tickets;
        sleep(1);  // Simulate delay
        available_tickets = current_tickets - 1;
        tickets_sold++;

        cout << "Ticket booked by Thread "
             << *((int*)arg)
             << " | Remaining Tickets = "
             << available_tickets << endl;
    }
    else
    {
        cout << "No tickets left! Thread "
             << *((int*)arg)
             << " could not book.\n";
    }

    pthread_mutex_unlock(&mutex_lock); // Unlock after critical section
    return NULL;
}

int main()
{
    pthread_t tA, tB;

    pthread_mutex_init(&mutex_lock, NULL); // Initialize mutex

    int id1 = 1, id2 = 2;
    pthread_create(&tA, NULL, book_tickets, &id1);
    pthread_create(&tB, NULL, book_tickets, &id2);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    pthread_mutex_destroy(&mutex_lock); // Destroy mutex

    cout << "Total Tickets Sold = " << tickets_sold << endl;
    cout << "Tickets Left = " << available_tickets << endl;

    return 0;
}
