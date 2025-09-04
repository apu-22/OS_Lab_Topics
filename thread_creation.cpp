#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void* thread_fun(void* arg)
{
    cout << "we are right now inside the Thread:" << endl;
    for (int i = 1; i <= 5; i++)
    {
        cout << i << endl;
        sleep(1);
    }
    return nullptr;
}

int main()
{
    pthread_t td1;

    // Create thread
    pthread_create(&td1, nullptr, thread_fun, nullptr);

    // Wait for thread to finish
    pthread_join(td1, nullptr);

    cout << "Back to the main process:" << endl;
    for (int i = 6; i < 20; i++)
    {
        if (i % 2 == 0)
        {
            cout << i << endl;
            sleep(1);
        }
    }
    return 0;
}
