#include <R_W.h>
int RUN() {
    //pthread
    pthread_t tid; // the thread identifier
    pthread_attr_t attr; //set of thread attributes

    /* get the default attributes */
    pthread_attr_init(&attr);

    //initial the semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    readCount = 0;

    int id = 0;
    while(scanf("%d", &id) != EOF) {

        char role;      //producer or consumer
        int opTime;     //operating time
        int lastTime;   //run time

        scanf("%c%d%d", &role, &opTime, &lastTime);
        struct data* d = (struct data*)malloc(sizeof(struct data));

        d->id = id;
        d->opTime = opTime;
        d->lastTime = lastTime;

        if(role == 'R') {
            printf("Create the %d thread: Reader\n", id);
            pthread_create(&tid, &attr, Reader, d);

        }
        else if(role == 'W') {
            printf("Create the %d thread: Writer\n", id);
            pthread_create(&tid, &attr, Writer, d);
        }
    }

    //信号量销毁
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
