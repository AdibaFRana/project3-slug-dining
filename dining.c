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

void check_lock(pthread_mutex_t *x) {
  pthread_mutex_lock(x);
  pthread_mutex_unlock(x);
}

typedef struct dining {
  // TODO: Add your variables here
  int capacity;
  // number of empty seats
  int empty_seats;
  // lock on dining door when cleaning is present
  // 0 is unlocked
  // 1 is locked
  pthread_mutex_t *lock;
} dining_t;

dining_t *dining_init(int capacity) {
  // TODO: Initialize necessary variables
  dining_t *dining = malloc(sizeof(dining_t));
  dining->capacity = capacity;
  // initialize empty_seats
  dining->empty_seats = capacity;
  // initialize lock
  dining->lock = calloc(1, sizeof(pthread_mutex_t));
  pthread_mutex_init(dining->lock, NULL);
  return dining;
}
void dining_destroy(dining_t **dining) {
  // TODO: Free dynamically allocated memory
  // no need to free empty_seats
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
  down(&(dining->empty_seats));
}

void dining_student_leave(dining_t *dining) {
  // TODO: Your code goes here
  // increase empty seats
  up(&(dining->empty_seats));
}

void dining_cleaning_enter(dining_t *dining) {
  // TODO: Your code goes here
  // stop students from entering
  pthread_mutex_lock(dining->lock);
  // wait until hall empty
  while (dining->empty_seats != dining->capacity) {
    // busy wait
  }
}

void dining_cleaning_leave(dining_t *dining) {
  // TODO: Your code goes here
  // unlock door
  pthread_mutex_unlock(dining->lock);
}
