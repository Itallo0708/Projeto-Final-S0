#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// declarando recursos globais
int madeira = 0;
int pedra = 0;

// declarando semaforos
sem_t mutex_madeira;
sem_t mutex_pedra;

// definindo constantes
#define N_LENHADORES 10
#define M_MINERADORES 10
#define COLETA_TRABALHADOR 10

//função para coletar madeira
void *coleta_madeira(void* ponteiro_id){
    // recebe a id do lenhador
    int id = *((int*)ponteiro_id);
    free(ponteiro_id);
    for (int i = 0; i < COLETA_TRABALHADOR; i++){
       // tenda entrar na região crítica
       sem_wait(&mutex_madeira);
       // região crítica
       madeira++;
       printf("Lenhador %i coletou madeira! Total: %i\n", id, madeira);
       // saiu da região crítica

       //liberando recursos
       sem_post(&mutex_madeira);
       // simulação de tempo
       usleep(100000 + rand() % 100000);

    }
    pthread_exit(NULL);
}