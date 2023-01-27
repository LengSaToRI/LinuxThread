#ifndef R_W_H
#define R_W_H
#include <stdio.h>
#include <QDebug>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <Customer.h>

QMutex m_mutex;
//semaphores
static sem_t wrt,mutex;
static int readCount;

struct data {
    int id;
    int opTime;
    int lastTime;
};

//读者
void* Reader(void* param)
{
    int id = ((struct data*)param)->id;
    int lastTime = ((struct data*)param)->lastTime;
    tip[infotimes]="读线程[";
    tip[infotimes]+=QString::number(id);
    tip[infotimes]+="]";
    tip[infotimes]+="等待读取Read";
    infotimes++;
    sem_wait(&mutex);
    readCount++;
    if(readCount == 1)
    {
        sem_wait(&wrt);
    }
    sem_post(&mutex);
    tip[infotimes]="读线程[";
    tip[infotimes]+=QString::number(id);
    tip[infotimes]+="]";
    tip[infotimes]+="开始读取Read";
    infotimes++;
    sleep(lastTime);
    tip[infotimes]="读线程[";
    tip[infotimes]+=QString::number(id);
    tip[infotimes]+="]";
    tip[infotimes]+="结束读取Read";
    infotimes++;
    sem_wait(&mutex);
    readCount--;
    if(readCount == 0)
    {
        sem_post(&wrt);
    }
    sem_post(&mutex);
    pthread_exit(0);
    return 0;
}

//写者
void* Writer(void* param)
{
    int id = ((struct data*)param)->id;
    int lastTime = ((struct data*)param)->lastTime;
    int opTime = ((struct data*)param)->opTime;

    sleep(opTime);
    tip[infotimes]="写线程[";
    tip[infotimes]+=QString::number(id);
    tip[infotimes]+="]";
    tip[infotimes]+="等待写入Write";
    infotimes++;
    sem_wait(&wrt);
    tip[infotimes]="写线程[";
    tip[infotimes]+=QString::number(id);
    tip[infotimes]+="]";
    tip[infotimes]+="开始写入Write";
    infotimes++;
    sleep(lastTime);
    tip[infotimes]="写线程[";
    tip[infotimes]+=QString::number(id);
    tip[infotimes]+="]";
    tip[infotimes]+="结束写入Write";
    infotimes++;
    sem_post(&wrt);
    pthread_exit(0);
    return 0;
}
#endif // R_W_H
