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
void *coletar_madeira(void* ponteiro_id){
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

// função para coletar pedra

void *coleta_pedra( void* ponteiro_id ){
    // recebe a id do minero
    int id = *((int*)ponteiro_id);
    free(ponteiro_id);

    for (int i = 0; i < COLETA_TRABALHADOR; i++){
        // tenta entrar na região crítica
        sem_wait(&mutex_pedra);
        // região crítica
        pedra++;
        printf("Minero %i coletou pedra! Total: %i\n", id, pedra);
        // saiu da região crítica

        // libera semáforo
        sem_post(&mutex_pedra);
        // simulação de tempo
        usleep(100000 + rand() % 100000);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t lenhadores[N_LENHADORES];
    pthread_t mineradores[M_MINERADORES];

    //incializar os semáforos 
    sem_init(&mutex_madeira, 0, 1);
    sem_init(&mutex_pedra, 0, 1);

    printf("Inicizalizando a coleta de recursos\n");

    // criar threads para os lenhadores
    for (int i = 0; i < N_LENHADORES; i++){
        int* id = malloc(sizeof(int));
        *id = i + 1;
        if (pthread_create(&lenhadores[i], NULL, coletar_madeira, (void*)id) != 0){
            printf("Erro ao criar a thread dos lenhadores!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    // criar threads para os mineradores
    for (int i = 0; i <M_MINERADORES; i++){
        int* id = malloc(sizeof(int));
        *id = i + 1;
        
        if (pthread_create(&mineradores[i], NULL, coleta_pedra, (void*)id) != 0){
            printf("Erro ao criar threads dos mineradores!\n");
            exit(EXIT_FAILURE);
        }
    }

    // agurda a finalização das threads dos lenhadores
    for (int i = 0; i < N_LENHADORES; i++){
        pthread_join(lenhadores[i], NULL);
    }

    // aguarda a finalização das threads dos mineradores
    for (int i = 0; i < M_MINERADORES; i++){
        pthread_join(mineradores[i], NULL);
    }

    // destroindo semaáforos após o uso
    sem_destroy(&mutex_madeira);
    sem_destroy(&mutex_pedra);

    // resultados
    printf("\n Coleta Finalizada!\n");
    printf("Total de madeira: %i\n", madeira);
    printf("Total esperado de madeira na coleta: %i\n", N_LENHADORES * COLETA_TRABALHADOR);
    printf("Total de pedra: %i\n", pedra);
    printf("Total de pedra esperado: %i\n", M_MINERADORES * COLETA_TRABALHADOR);

    return 0;
}