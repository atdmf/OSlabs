#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define BUFFER_SIZE 7

using namespace std;


bool thr1_cancel = false;
bool thr2_cancel = false;

int filedes[2];

static void* thread1_start(void* args)
{
    cout << "ПОТОК 1 НАЧАЛ РАБОТУ \n" << flush;
    char buf[BUFFER_SIZE];
    while(!thr1_cancel)
    {
        strcpy(buf, "Hello!");
        write(filedes[1],buf,BUFFER_SIZE);
        sleep(1);
    }   
    cout << "ПОТОК 1 ЗАКОНЧИЛ РАБОТУ \n" << flush;
}

static void* thread2_start(void* args)
{
    cout << "ПОТОК 2 НАЧАЛ РАБОТУ \n" << flush;
    char buf[BUFFER_SIZE];
    while(!thr2_cancel)
    {
        memset(buf, 0, sizeof(buf));
        read(filedes[0],buf,BUFFER_SIZE);
        for(int i = 0; i < BUFFER_SIZE; i++)
        {
            cout << buf[i] << std::flush;
        }
        sleep(1);
    }   
    cout << "ПОТОК 2 ЗАКОНЧИЛ РАБОТУ \n" << flush;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "НАЧАЛО РАБОТЫ ОСНОВНОЙ ПРОГРАММЫ \n" << flush;
    pthread_t thread1;
    pthread_t thread2;
    pipe(filedes);
    fcntl(filedes[0], F_SETFL, O_NONBLOCK);
    fcntl(filedes[1], F_SETFL, O_NONBLOCK);
    pthread_create(&thread1, NULL,thread1_start, NULL);
    pthread_create(&thread2, NULL,thread2_start, NULL);
    getchar();
    thr1_cancel = true;
    thr2_cancel = true;
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    close(filedes[0]);
    close(filedes[1]);
    cout << "КОНЕЦ\n" << flush;
    return 0;
}