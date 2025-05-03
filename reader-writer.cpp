/*
 Author : Ayush Chavan
 CF ID : YSlow
*/
#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
using namespace std;

sem_t block_reader , db;
int read_cnt;

void* reader(void *id)
{
    int r_id = *((int*) id);
    sem_wait(&block_reader);
    ++read_cnt;

    if(read_cnt==1)
    {
       sem_wait(&db);
    }

    cout << "reader : " << r_id << endl;

    sem_post(&block_reader);
    --read_cnt;

    cout << "reader leaving : " << r_id << endl;

    if(read_cnt == 0)
    {
        sem_post(&db);
    }

    return NULL;
}

void* writer(void *id)
{
    int w_id = *((int*)id);
    sem_wait(&db);

    cout << "writer : " << w_id << endl;

    sem_post(&db);

    return NULL;
}

int main()
{
    pthread_t r[5] , w[2];
    sem_init(&block_reader, 0, 1);
    sem_init(&db, 0, 1);
    int r_id[5] = {1, 2, 3 , 4 , 5} , w_id[2] = {1, 2};
    for (int i = 0; i <= 4; ++i)
    {
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    }

    for (int i = 0; i <= 1; ++i)
    {
        pthread_create(&w[i], NULL, writer, &w_id[i]);
    }

    for (int i = 0; i < 5; ++i)
    {
        pthread_join(r[i], NULL);
    }

    for (int i = 0; i < 2; ++i)
    {
        pthread_join(w[i], NULL);
    }


    sem_destroy(&block_reader);
    sem_destroy(&db);

    return 0;
}