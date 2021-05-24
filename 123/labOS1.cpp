#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

static void* thread1_start(void* arg)
{
    
    cout << "\n ПОТОК 1 НАЧАЛ РАБОТУ" << endl;
    bool* ptr = (bool *) arg;
    while(!*ptr)
    {
        cout << '1';
        sleep(1);
    }
    int* retval_1 = new int;
    *retval_1 = 5;
    cout << "\n ПОТОК 1 ЗАВЕРШИЛ РАБОТУ" << endl;
    pthread_exit(retval_1);
    
}

static void* thread2_start(void* arg)
{
    cout << "\n ПОТОК 2 НАЧАЛ РАБОТУ" << endl;
    bool* ptr = (bool *) arg;
    while(!*ptr)
    {      
        cout << '2';
        sleep(1);
    }
    int* retval_2 = new int;
    *retval_2 = 10;
    cout << "\n ПОТОК 2 ЗАВЕРШИЛ РАБОТУ" << endl;
    pthread_exit(retval_2);
    
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Старт программы" << endl;
    bool cancel_thread_1 = false;
    bool cancel_thread_2 = false;
    int* ptr_t1;
    int* ptr_t2;


    pthread_t thread_1;
    pthread_t thread_2;
    pthread_create(&thread_1, NULL, thread1_start, &cancel_thread_1);
    pthread_create(&thread_2, NULL, thread2_start, &cancel_thread_2);
    cout << "Нажмите любую клавишу" << endl;
    getchar();
    cout << endl;
    cancel_thread_1 = true;
    cancel_thread_2 = true;
    pthread_join(thread_1, (void**)&ptr_t1);
    pthread_join(thread_2, (void**)&ptr_t2);
    cout << "Возвращение значения потока 1- " << *ptr_t1 << endl;
    delete ptr_t1;
    cout << "Возвращение значения потока 2- " << *ptr_t2 << endl;
    delete ptr_t2;
    cout << "Выход из программы" << endl;
    return 0;
}