#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_BOWLS 5
#define NUM_CHEFS 2
#define NUM_DELIVERY 3
#define TOTAL_BOWLS_TO_MAKE 15

// semaphores
sem_t empty_slots; 
sem_t full_slots;  
sem_t mutex;       

// shared variables
int counter = 0;          
int total_made = 0;       
int total_delivered = 0;  
int shop_open = 1;        

void* chef(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&mutex);
        if (total_made >= TOTAL_BOWLS_TO_MAKE) {
            sem_post(&mutex);
            break;
        }
        total_made++;
        int my_bowl = total_made;
        sem_post(&mutex);

        printf("[Chef %d]     is making poki bowl %d...\n", id, my_bowl);
        usleep(400000); 

        sem_wait(&empty_slots);
        
        sem_wait(&mutex);
        counter++;
        printf("[Chef %d]     put poki bowl %d on the counter. (Bowls on counter: %d)\n", id, my_bowl, counter);
        sem_post(&mutex);
        
        sem_post(&full_slots);
    }
    return NULL;
}

void* delivery(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&full_slots);

        sem_wait(&mutex);
        if (!shop_open && counter == 0) {
            sem_post(&mutex);
            sem_post(&full_slots); // cascade wake-up
            break;
        }
        counter--;
        total_delivered++;
        int my_delivery = total_delivered;
        printf("[Delivery %d] picked up poki bowl %d. (Bowls on counter: %d)\n", id, my_delivery, counter);
        sem_post(&mutex);
        
        sem_post(&empty_slots);

        printf("[Delivery %d] is out delivering poki bowl %d...\n", id, my_delivery);
        usleep(700000); 
    }
    return NULL;
}

int main() {
    printf("--- poki restaurant open! ---\n\n");

    pthread_t chefs[NUM_CHEFS];
    pthread_t deliveries[NUM_DELIVERY];
    int chef_ids[NUM_CHEFS];
    int delivery_ids[NUM_DELIVERY];

    sem_init(&empty_slots, 0, MAX_BOWLS);  
    sem_init(&full_slots, 0, 0);           
    sem_init(&mutex, 0, 1);                

    for (int i = 0; i < NUM_CHEFS; i++) {
        chef_ids[i] = i + 1;
        pthread_create(&chefs[i], NULL, chef, &chef_ids[i]);
    }

    for (int i = 0; i < NUM_DELIVERY; i++) {
        delivery_ids[i] = i + 1;
        pthread_create(&deliveries[i], NULL, delivery, &delivery_ids[i]);
    }

    for (int i = 0; i < NUM_CHEFS; i++) {
        pthread_join(chefs[i], NULL);
    }
    
    sem_wait(&mutex);
    shop_open = 0;
    sem_post(&mutex);
    
    // wake up any delivery drivers stuck waiting
    for (int i = 0; i < NUM_DELIVERY; i++) {
        sem_post(&full_slots);
    }

    for (int i = 0; i < NUM_DELIVERY; i++) {
        pthread_join(deliveries[i], NULL);
    }

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    sem_destroy(&mutex);

    printf("\n--- All %d poki bowls have been made and delivered. poki restaurant is closed! ---\n", total_delivered);
    return 0;
}