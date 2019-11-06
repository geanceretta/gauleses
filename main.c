#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t *mutex, *sem_full, *sem_cozinhar;
int javalis_grelhados = 0;

//TODO generic process receiving a struct as parameter, containing process_name and a list of semaphores to wait and to post

void* process_g(void* unused){
    while(1){
        sem_wait(mutex);
        if (javalis_grelhados == 0) {
            printf("Javali g(0) acordou o cozinheiro\n");
            sem_post(sem_cozinhar);
            sem_wait(sem_full);
        }
        printf("Gaules g(0) comendo javali %d\n", javalis_grelhados);
        javalis_grelhados--;
        sem_post(mutex);
        //sleep((rand()%4)+1);
    }
    pthread_exit(NULL);
}

void* process_e(void* unused){
    while(1){
        sem_wait(mutex);
        if (javalis_grelhados == 0) {
            printf("Javali e(1) acordou o cozinheiro\n");
            sem_post(sem_cozinhar);
            sem_wait(sem_full);
        }
        printf("Gaules e(1) comendo javali %d\n", javalis_grelhados);
        javalis_grelhados--;
        sem_post(mutex);
        //sleep((rand()%4)+1);
    }
    pthread_exit(NULL);
}

void* process_a(void* unused){
    while(1){
        sem_wait(mutex);
        if (javalis_grelhados < 1) {
            printf("Javali a(2) acordou o cozinheiro\n");
            sem_post(sem_cozinhar);
            sem_wait(sem_full);
        }
        printf("Gaules a(2) comendo javali %d\n", javalis_grelhados);
        javalis_grelhados--;
        sem_post(mutex);
        //sleep((rand()%4)+1);
    }
    pthread_exit(NULL);
}

void* process_n(void* unused){
    while(1){
        sem_wait(mutex);
        if (javalis_grelhados < 1) {
            printf("Javali n(3) acordou o cozinheiro\n");
            sem_post(sem_cozinhar);
            sem_wait(sem_full);
        }
        printf("Gaules n(3) comendo javali %d\n", javalis_grelhados);
        javalis_grelhados--;
        //sleep((rand()%4)+1);
        sem_post(mutex);
    }
    pthread_exit(NULL);
}

void* process_c(void* unused){
    while(1){
        sem_wait(sem_cozinhar);
        while(javalis_grelhados < 10){
            //sleep((rand()%4)+1);
            javalis_grelhados++;
            printf("cozinheiro grelhando javali %d...\n", javalis_grelhados);
        }
        sem_post(sem_full);
    }
    pthread_exit(NULL);
}

int main (void){
    // Close previous semaphores
    sem_close(mutex);
    sem_close(sem_full);
    sem_close(sem_cozinhar);
    
    // Unlink previous named semaphores
    sem_unlink("/mutex");
    sem_unlink("/sem_full");
    sem_unlink("/sem_cozinhar");

    // Semaphores initialization
    mutex = sem_open("/mutex", O_CREAT, 0644, 1);
    sem_full = sem_open("/sem_full", O_CREAT, 0644, 0);
    sem_cozinhar = sem_open("/sem_cozinhar", O_CREAT, 0644, 0);

    // Threads creation
    pthread_t thread_g, thread_e, thread_a, thread_n, thread_c;
    pthread_create(&thread_g,NULL,process_g,NULL);
    pthread_create(&thread_e,NULL,process_e,NULL);
    pthread_create(&thread_a,NULL,process_a,NULL);
    pthread_create(&thread_n,NULL,process_n,NULL);
    pthread_create(&thread_c,NULL,process_c,NULL);

    // Wait all threads to finish
    pthread_join(thread_g, NULL);
    pthread_join(thread_e, NULL);
    pthread_join(thread_a, NULL);
    pthread_join(thread_n, NULL);
    pthread_join(thread_c, NULL);
    
    // Close named semaphores
    sem_close(mutex);
    sem_close(sem_full);
    sem_close(sem_cozinhar);
    
    // Unlink named semaphores
    sem_unlink("/mutex");
    sem_unlink("/sem_full");
    sem_unlink("/sem_cozinhar");
}
