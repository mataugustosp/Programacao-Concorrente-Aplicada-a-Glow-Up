/*
 * Programação Concorrente Aplicada ao reality show de maquiagem "Glow Up"
 * Aluno: Matheus Augusto Silva Pinho
 * Matrícula: 18/0024906
 *
 * Simulação do primeiro episódio de Glow Up - 4º Temporada
 */

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// Defines
#define MUAS 10

// Variáveis
pthread_t tid[MUAS], val;
int episode, apresentados, ganhador = 0, faceoff1, faceoff2, eliminado;

// Vetor com todos os MUAs da teporada 4 de glow up
char *artistas[10] = {"Adam", "Charlie", "Kris", "Lisa", "Mikaél", "Nancé", "Rachel", "Ryan", "Sophie", "Yong-Chin"};

// Funcoes
void *make_up_artists(void *meuid);
void *jurados(void *meuid);

// Semaforos

sem_t *artist;
sem_t *judge;
sem_t *desafio_inicial;
sem_t *faceoff;
sem_t *faceoffel;

int main(argc, argv)
int argc;
char *argv[];
{
    int i;
    int *id;
    episode = 1;
    /*********** Semaforos *************/

    sem_unlink("artist");
    artist = sem_open("artist", O_CREAT, 0777, 0);
    if (artist == SEM_FAILED)
    {
        fprintf(stderr, "%s\n", "ERROR creating semaphore artist");
        exit(EXIT_FAILURE);
    }

    sem_unlink("desafio_inicial");
    desafio_inicial = sem_open("desafio_inicial", O_CREAT, 0777, 1);
    if (desafio_inicial == SEM_FAILED)
    {
        fprintf(stderr, "%s\n", "ERROR creating semaphore desafio_inicial");
        exit(EXIT_FAILURE);
    }

    sem_unlink("faceoff");
    faceoff = sem_open("faceoff", O_CREAT, 0777, 1);
    if (faceoff == SEM_FAILED)
    {
        fprintf(stderr, "%s\n", "ERROR creating semaphore faceoff");
        exit(EXIT_FAILURE);
    }

    sem_unlink("faceoffel");
    faceoffel = sem_open("faceoff", O_CREAT, 0777, 1);
    if (faceoffel == SEM_FAILED)
    {
        fprintf(stderr, "%s\n", "ERROR creating semaphore faceoffel");
        exit(EXIT_FAILURE);
    }

    sem_unlink("judge");
    judge = sem_open("judge", O_CREAT, 0777, 0);
    if (judge == SEM_FAILED)
    {
        fprintf(stderr, "%s\n", "ERROR creating semaphore judge");
        exit(EXIT_FAILURE);
    }

    /*********** Maya Jama apresenta introduz o programa *************/

    system("clear");
    printf("\n[Maya Jama]\n");
    sleep(1);
    printf("Uma revolução de maquiagem se iniciou em quartos de norte a sul do país\n");
    sleep(2);
    printf("Agora, entre milhares de inscritos, 10 maquiadores aspirantes terão a");
    sleep(2);
    printf(" oportunidade de mostrar seu talento.\n");
    sleep(2);
    printf("Para isso, precisarão mostrar TÉCNICA, ARTE e IMAGINAÇÃO.\n\n");
    sleep(2);
    printf("É HORA DO...\n\n");
    sleep(1);
    printf("\x1b[35m");

    printf("::::::::   :::        ::::::::  :::       :::      :::    ::: ::::::::: \n");
    sleep(1);
    printf(":+:    :+: :+:       :+:    :+: :+:       :+:      :+:    :+: :+:    :+:\n");
    sleep(1);
    printf("+:+        +:+       +:+    +:+ +:+       +:+      +:+    +:+ +:+    +:+\n");
    sleep(1);
    printf(":#:        +#+       +#+    +:+ +#+  +:+  +#+      +#+    +:+ +#++:++#+\n");
    sleep(1);
    printf("+#+   +#+# +#+       +#+    +#+ +#+ +#+#+ +#+      +#+    +#+ +#+       \n");
    sleep(1);
    printf("#+#    #+# #+#       #+#    #+#  #+#+# #+#+#       #+#    #+# #+#       \n");
    sleep(1);
    printf(" ########  ########## ########    ###   ###         ########  ###       \n");
    sleep(1);
    system("clear");

    // Já é anunciado o primeiro desafio que os MUAs tem que realizar
    printf("\033[0m");
    printf("\n\n******************* DESAFIO INICIAL ****************** \n");
    printf("\n[Val Garland] Olá MUAs! Bem-vindos a quarta temporada de Glow Up.\n");
    sleep(4);
    printf("\n[Dominc Skinner] Hoje, vocês terão que criar uma maquiagem fitness inovadora que chame a atenção dos clientes para o feed da Gymshark.");
    sleep(4);
    printf("\n\n[Val Garland] O artista que tiver o melhor desempenho ganhará a oportunidade de estrelar em uma campanha da empresa.\n");
    sleep(10);

    /*** Criacao de Threads ***/

    // Thread Jurados
    id = (int *)malloc(sizeof(int));
    *id = 0;
    pthread_create(&(val), NULL, jurados, (void *)id);

    // Threads MUAS
    for (i = 0; i < MUAS; i++)
    {
        id = (int *)malloc(sizeof(int));
        *id = i;
        pthread_create(&tid[i], NULL, make_up_artists, (void *)(id));
    }

    for (i = 0; i < MUAS; i++)
    {
        pthread_join(tid[0], NULL);
    }

    pthread_join(val, NULL);

}

void *jurados(void *arg)
{
    while (episode)
    {
        sem_wait(judge);
        // DESAFIO INICIAL 
        // Val, Dominc e convidada julgam as melhores e piores maquiagens 

        apresentados = 0;
        faceoff1 = 0;
        faceoff2 = 0;
    
        // Julgamento através de uma escolha randômica 
        srand(time(NULL));
        while (ganhador == faceoff1 || ganhador == faceoff2 || faceoff2 == faceoff1)
        {
            ganhador = rand() % MUAS;
            faceoff1 = rand() % MUAS;
            faceoff2 = rand() % MUAS;
        }
        // Anunciam as melhores e piores makes 
        printf("\n\n******************* Val, Dominc e convidada julgam  ****************** \n");
        printf("\n[Dominc Skinner] Os que tiveram pior performance e serão penalizados no próximo desafio são ... %s e %s.", artistas[faceoff1], artistas[faceoff2]);
        sleep(2);
        printf("\n\n%s, e %s Vocês terão 15 minutos a menos para completar sua make,", artistas[faceoff1], artistas[faceoff2]);
        sleep(4);
        printf("\n\n[Val Garland] O premiado de hoje que irá estrear uma campanha com a Gymshark é o MUA %s, PARABÉNS!!! \n\n", artistas[ganhador]);
        sleep(10);
        system("clear");

        // Desafio principal 
        printf("\n******************* DESAFIO PRINCIPAL ******************\n");
        printf("\n[Dominc Skinner] Neste desafio, vocês terão 2 horas para executar em vocês mesmos uma maquiagem artística que represente sua força oculta.\n");
        sleep(2);
        printf("\n[Val Garland] ARRASEM!!!\n");
        sleep(2);

        apresentados = 0;
        // Libera os artistas para executarem o desafio principal
        for (int i = 0; i < 10; i++)
        {
            sem_post(artist);
        }
        // Se bloqueia e espera os MUAs completarem a tarefa 
        sem_wait(judge);
        printf("\n\n******************* JULGAMENTO ****************** \n");
        while (ganhador == faceoff1 || ganhador == faceoff2 || faceoff2 == faceoff1)
        {
            ganhador = rand() % MUAS;
            faceoff1 = rand() % MUAS;
            faceoff2 = rand() % MUAS;
        }

        printf("\n[Val Garland] DING DONG DARLING o artista %s arrasou demais nesta disputa\n", artistas[ganhador]);
        sleep(4);
        printf("\n[Dominc Skinner] Os artistas de make que irão para a face off elimination esse semana são %s e %s\n", artistas[faceoff1], artistas[faceoff2]);
        sleep(5);

        // Cancela todos os MUAs que não estão no face off elimintion 
        for (int i = 0; i < MUAS; i++)
        {
            if((i != faceoff1) && (i != faceoff2))
            {
                pthread_cancel(tid[i]);
            }
        }
        //FACE OFF ELIMINATION 
        system("clear");
        printf("\n\n******************* FACE OFF ELIMINATION ****************** \n");
        sleep(1);
        printf("\n[Dominc Skinner] Para se livrarem da eliminação de hoje, vocês terão que fazer na modelo um Reverse Cat Eye\n");
        sleep(2);
        printf("\n[Val Garland] Vocês terão 15 minutos para concluir a tarefa \n");
        sleep(2);
        apresentados = 0;
        // Libera os dois MUAs restantes para competirem no Face off Chairs 
        sem_post(artist);
        sem_post(artist);

        // Se bloqueia e espera a competição 
        sem_wait(judge);
        // Val anuncia quem será elimindao
        printf("\n\n******************* ELIMINAÇÃO ****************** \n");
        sleep(1);
        printf("\n[Val Garland] %s pack your kit! Você é o eliminado de hoje", artistas[eliminado]);
        sleep(2);
        // Fim do primeiro episódio da temporada

        printf("\n****** FIM DO EPISÓDIO ******");
        episode = 0;
    }
    pthread_exit(0);
}

void *make_up_artists(void *pi)
{
    int code = *((int *)pi);
    if (episode)
    {
        // DESAFIO INICIAL
        sem_wait(desafio_inicial);
        apresentados++;
        printf("\nO MUA %s concluiu sua make e está apresentando", artistas[code]);
        sleep(1);
        if (apresentados >= 10)
        {
            sem_post(judge);
        }
        sem_post(desafio_inicial);

        // DESAFIO PRINCIPAL
        sem_wait(artist);
        sem_wait(faceoff);
        apresentados++;
        if (code == faceoff1 || code == faceoff2)
        {
            printf("\n %s entregou e está apresentando sua maquiagem depois de cumprir a penalidade de 15 minutos", artistas[code]);
        }
        else
        {
            printf("\n %s entregou e está apresentando sua maquiagem ", artistas[code]);
        }
        sleep(1);
        if (apresentados == 10)
        {
            apresentados = 0;
            faceoff1 = 0;
            faceoff2 = 0;
            sem_post(judge);
        }
        sem_post(faceoff);
        sem_wait(artist);

        // FACE OFF ELIMINATION 
        sem_wait(faceoffel);
        apresentados++;   
        printf("\nO MUA %s concluiu sua make e está apresentando", artistas[code]);
        // O último a chegar libera o Juiz e é o eliminado da semana.
        if (apresentados == 2)
        {
            eliminado = code;
            sem_post(judge);
        }
        sem_post(faceoffel);
        sem_wait(artist);
    }
    pthread_exit(0);
}
