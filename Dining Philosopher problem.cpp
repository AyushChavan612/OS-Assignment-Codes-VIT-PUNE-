#include<iostream>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

using namespace std;
// #define endl '\n'

const int size = 5;
sem_t forks[size];
sem_t room;

void* eat(void* id)
{
    int phil_id = *((int*)id);
    while (true)
    {
        cout << "philosopher : " << phil_id << " is thinking" << endl;
        // cout.flush();
        sleep(1);

        sem_wait(&room);
        sem_wait(&forks[phil_id - 1]);
        sem_wait(&forks[phil_id % size]);

        cout << "philosopher : " << phil_id << " is eating" << endl;
        // cout.flush();
        sleep(2);

        sem_post(&forks[phil_id % size]);
        sem_post(&forks[phil_id - 1]);
        sem_post(&room);
    }

    return NULL;
}

int main()
{
    pthread_t phils[size];
    int id[size] = {1, 2, 3, 4, 5};

    for (int i = 0; i < size; ++i)
        sem_init(&forks[i], 0, 1);

    sem_init(&room, 0, size - 1);

    for (int i = 0; i < size; ++i)
        pthread_create(&phils[i], NULL, eat, &id[i]);

    for (int i = 0; i < size; ++i)
        pthread_join(phils[i], NULL);

    for (int i = 0; i < size; ++i)
        sem_destroy(&forks[i]);

    return 0;
}
