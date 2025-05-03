/*
 Author : Ayush Chavan
 CF ID : YSlow
*/
#include<iostream>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

const int mxN = 5;
int buffer[mxN];
int in = 0 , out = 0;
sem_t empty , full , mutex;

void* producer(void*)
{
    int item = 1;
    while (item <= 10)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        cout << "produced : " << item << endl;
        buffer[in++] = item;
        in %= mxN;

        sem_post(&mutex);
        sem_post(&full);
        item++;
    }

    return NULL;
}

void* consumer(void *)
{
    for (int i = 1; i <= 10; ++i)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out++];
        out %= mxN;

        cout << "consumed : " << item << endl;

        sem_post(&mutex);
        sem_post(&empty);
    }

    return NULL;
}

int main()
{

    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, mxN);

    pthread_t prod , con;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(con, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}