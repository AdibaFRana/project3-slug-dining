#include "dining.h"

#include <pthread.h>
#include <stdlib.h>

void up(int *sem) { (*sem)++; }

void down(int *sem) {
  while ((*sem) <= 0) {
    //  busy wait
  }
  (*sem) -= 1;
}

void lock(int *x) { (*x) = 1; }

void unlock(int *x) { (*x) = 0; }

void check_lock(int *x) {
  while ((*x) == 1) {
    // busy wait
  }
}

typedef struct dining {
  // TODO: Add your variables here
  int capacity;
  // number of empty seats
  int empty_seats;
  // lock on dining door when cleaning is present
  // 0 is unlocked
  // 1 is locked
  int lock;
} dining_t;

dining_t *dining_init(int capacity) {
  // TODO: Initialize necessary variables
  dining_t *dining = malloc(sizeof(dining_t));
  dining->capacity = capacity;
  // initialize empty_seats
  dining->empty_seats = capacity;
  // initialize lock
  dining->lock = 0;
  return dining;
}
void dining_destroy(dining_t **dining) {
  // TODO: Free dynamically allocated memory
  free(*dining);
  *dining = NULL;
  // no need to free empty_seats
  // no need to free lock
}

void dining_student_enter(dining_t *dining) {
  // TODO: Your code goes here
  // decrease empty seats
  check_lock(&(dining->lock));
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
  lock(&(dining->lock));
  // wait until hall empty
  while (dining->empty_seats != dining->capacity) {
    // busy wait
  }
}

void dining_cleaning_leave(dining_t *dining) {
  // TODO: Your code goes here
  // unlock door
  unlock(&(dining->lock));
}
