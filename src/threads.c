/*
** EPITECH PROJECT, 2022
** B-CCP-400-STG-4-1-panoramix-timothe.coniel
** File description:
** threads
*/

#include "../include/panoramix.h"

static parameters_t *params;
static pthread_mutex_t make_potion;
static sem_t semaphore_village;
static sem_t semaphore;
static pthread_mutex_t go_fight;

static void free_threads(int *ids, pthread_t *threads)
{
    free(ids);
    free(threads);
    sem_destroy(&semaphore);
    sem_destroy(&semaphore_village);
}

static int call_panoramix(int ids)
{
    printf("Villager %d: I need a drink... I see %d servings left.\n", \
        ids, params->pot_size);
    if (params->pot_size == 0) {
        printf("Villager %d: Hey Pano wake up! We need more potion.\n", ids);
        sem_post(&semaphore_village);
        sem_wait(&semaphore);
    }
    params->pot_size--;
    return (1);
}

static void *villagers(void *id)
{
    int fights = params->nb_fights;
    int *ids = id;
    int i = 0;

    printf("Villager %d: I'm going into the fight.\n", *ids);
    while (fights != 0 || (params->nb_refills == 0 && params->pot_size == 0)) {
        if (params->pot_size >= 0) {
            pthread_mutex_lock(&go_fight);
            call_panoramix(*ids);
            pthread_mutex_unlock(&go_fight);
        }
        printf("Villager %d: Take that roman scum! " \
            "Only %d left.\n", *ids, fights);
        fights--;
    }
    printf("Villager %i: I'm going to sleep now.\n", *ids);
}

void *panoramix(void *id)
{
    int potion_created = 0;
    int i = 0;

    printf("Druid: I'm ready... but sleepy...\n");
    while (params->nb_refills >= 0) {
        sem_wait(&semaphore_village);
        printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware" \
            " I can only make %d more refills after this one.\n", \
            params->nb_refills);
        params->pot_size = params->initial_pot_size;
        params->nb_refills--;
        if (params->nb_refills == 0) {
            printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
            sem_post(&semaphore);
            break;
        }
        sem_post(&semaphore);
    }
}

int threads(parameters_t *parameter)
{
    pthread_t* threads;
    int *ids;

    pthread_mutex_init(&make_potion, NULL);
    pthread_mutex_init(&go_fight, NULL);
    sem_init(&semaphore, PTHREAD_PROCESS_SHARED, 0);
    sem_init(&semaphore_village, PTHREAD_PROCESS_SHARED, 0);
    params = parameter;
    threads = malloc((params->nb_villager + 1) * sizeof(pthread_t));
    ids = malloc(params->nb_villager * sizeof(int));
    for (int i = 0; i < params->nb_villager; i++)
        ids[i] = i;
    pthread_create(&threads[params->nb_villager], NULL, panoramix, (void *)0);
    for (int i = params->nb_villager - 1; i >= 0; i--)
        pthread_create(&threads[i], NULL, villagers, (void *)&ids[i]);
    for (int i = 0; i < params->nb_villager; i++)
        pthread_join(threads[i], NULL);
    free_threads(ids, threads);
    return (0);
}