#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;

struct thread_args
{
    bool thread_cancel_flag = false;
    sem_t* arg_semaphore;

};

static void* thread1_start(void* args)
{
    thread_args* t1 = (thread_args* ) args;
    cout << "ПОТОК 1 НАЧАЛ РАБОТУ \n" << flush;
    while(!t1->thread_cancel_flag)
    {
        sem_wait(t1->arg_semaphore);
        for(int i = 0; i<5; i++)
        {
            cout << '1' << flush;
            sleep(1);
        }
        sem_post(t1->arg_semaphore);
        sleep(1);
    }   
    cout << "ПОТОК 1 ЗАВЕРШИЛ РАБОТУ \n" << flush;
}

static void* thread2_start(void* args)
{
    thread_args* t2 = (thread_args* ) args;
    cout << "ПОТОК 2 НАЧАЛ РАБОТУ \n" << flush;
    while(!t2->thread_cancel_flag)
    {
        sem_wait(t2->arg_semaphore);
        for(int i = 0; i<5; i++)
        {
            cout << '2' << flush;
            sleep(1);
        }
        sem_post(t2->arg_semaphore);
        sleep(1);
    }   
    cout << "ПОТОК 2 ЗАВЕРШИЛ РАБОТУ \n" << flush;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    sem_t semaphore;
    thread_args t1_args;
    thread_args t2_args;
    t1_args.arg_semaphore = &semaphore;
    t2_args.arg_semaphore = &semaphore;
    cout << "НАЧАЛО РАБОТЫ ОСНОВНОЙ ПРОГРАММЫ \n" << flush;
    pthread_t thread1;
    pthread_t thread2;
    sem_init(&semaphore,0,1);
    pthread_create(&thread1, NULL,thread1_start, &t1_args);
    pthread_create(&thread2, NULL,thread2_start, &t2_args);
    getchar();
    t1_args.thread_cancel_flag = true;
    t2_args.thread_cancel_flag = true;
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&semaphore);
    cout << "КОНЕЦ \n" << flush;
    return 0;
} 
