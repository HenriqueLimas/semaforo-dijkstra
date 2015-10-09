#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <pthread.h>

typedef struct {
  pthread_mutex_t lock;
  pthread_cond_t wait;
  int counter;
} semaforo;

void error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

void* p(semaforo *s) {
  pthread_mutex_lock(&(s->lock));
  s->counter--;
  
  if (s->counter < 0) {
    pthread_cond_wait(&(s->wait), &(s->lock));
  }

  pthread_mutex_unlock(&(s->lock));
  return;
}

void* v(semaforo *s) {
  pthread_mutex_lock(&(s->lock));

  s->counter++;

  if (s->counter <= 0) {
    pthread_cond_signal(&(s->wait));
  }
  pthread_mutext_unlock(&(s->lock));
}


