#include "dining.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

void up(int *sem) { (*sem)++; }

void down(int *sem) {
  while ((*sem) <= 0) {
    //  busy wait
  }
  (*sem) -= 1;
}

void try_clean(int *cap, int *curr) {
  while ((*curr) != (*cap)) {
    // busy wait
  }
}

void check_lock(pthread_mutex_t *x) {
  pthread_mutex_lock(x);
  pthread_mutex_unlock(x);
}

typedef struct dining {
  // TODO: Add your variables here
  int capacity;
  // number of empty seats
  int empty_seats;
  sem_t *available_seats;
  // ready for clean
  sem_t *empty;
  // lock on dining door when cleaning is present
  // 0 is unlocked
  // 1 is locked
  pthread_mutex_t *lock;
} dining_t;

dining_t *dining_init(int capacity) {
  // TODO: Initialize necessary variables
  dining_t *dining = malloc(sizeof(dining_t));
  dining->capacity = capacity;
  // initialize available seats
  // dining->empty_seats = capacity;
  dining->available_seats = malloc(sizeof(sem_t));
  dining->empty = malloc(sizeof(sem_t));
  sem_init(dining->available_seats, 0, (unsigned int)capacity);
  sem_init(dining->empty, 0, 0);
  // initialize lock
  dining->lock = malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(dining->lock, NULL);
  return dining;
}
void dining_destroy(dining_t **dining) {
  // TODO: Free dynamically allocated memory
  // free available seats semaphore
  sem_destroy((*dining)->available_seats);
  sem_destroy((*dining)->empty);
  free((*dining)->available_seats);
  free((*dining)->empty);
  // free lock
  pthread_mutex_destroy((*dining)->lock);
  free((*dining)->lock);
  free(*dining);
  *dining = NULL;
}

void dining_student_enter(dining_t *dining) {
  // TODO: Your code goes here
  // decrease empty seats
  check_lock(dining->lock);
  // down(&(dining->empty_seats));
  sem_wait(dining->available_seats);
}

void dining_student_leave(dining_t *dining) {
  // TODO: Your code goes here
  // increase empty seats
  // up(&(dining->empty_seats));
  sem_post(dining->available_seats);
  int temp;
  sem_getvalue(dining->available_seats, &temp);
  if (temp == dining->capacity) {
    sem_post(dining->empty);
  }
}

void dining_cleaning_enter(dining_t *dining) {
  // TODO: Your code goes here
  // stop students from entering
  pthread_mutex_lock(dining->lock);
  // wait until hall empty
  // try_clean(&(dining->capacity), &(dining->empty_seats));
  sem_wait(dining->empty);
}

void dining_cleaning_leave(dining_t *dining) {
  // TODO: Your code goes here
  // unlock door
  pthread_mutex_unlock(dining->lock);
}
