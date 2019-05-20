// PROGRAMA p01.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>

#define MAXELEMS 10000000 // nr. max de posicoes
#define MAXTHREADS 100    // nr. max de threads
#define min(a, b) (a) < (b) ? (a) : (b)
 int *shm;


int npos;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // mutex p/a sec.critica
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;
int buf[MAXELEMS], pos = 0, val = 0; // variaveis partilhadas

void *fill(void *nr) {

  while (1) {
   // pthread_mutex_lock(&mut);
    if (pos >= npos) {
      // pthread_mutex_unlock(&mut);
      // pthread_mutex_unlock(&mut2);
      return NULL;
    }
    shm[pos]= val;
    pos++;
    val++;
    // pthread_mutex_unlock(&mut);
    // pthread_mutex_unlock(&mut2);
    *(int *)nr += 1;
  }

}

void *verify(void *arg) {
  int k;
  for (k = 0; k < npos; k++) {
    // pthread_mutex_lock(&mut2);
    if (buf[k] != k && k < pos) // detecta valores errados
      printf("ERROR: buf[%d] = %d\n", k, buf[k]);
    // pthread_mutex_unlock(&mut2);
  }

  return NULL;
}

int main(int argc, char *argv[]) {

  int k,count[MAXTHREADS];   // array para contagens
  int total;
  int np;

  int shmfd = shm_open("/shm1",O_CREAT|O_RDWR,0600);
  ftruncate(shmfd,10);
  shm = (int *) mmap(0,10,PROT_READ|PROT_WRITE,MAP_SHARED,shmfd,0);


  if (argc != 3) {
    printf("Usage: %s <nr_pos> <nr_thrs>\n", argv[0]);
    return 1;
  }

  npos = min(atoi(argv[1]), MAXELEMS);   // no. efectivo de posicoes
  np = min(atoi(argv[2]), MAXTHREADS); // no. efectivo de threads

  for (k = 0; k < np; k++) { // criacao das threads 'fill'
   if(fork() == 0)
   {
       fill(&count[k]);
       total += count[k];
   }
  }


  printf("total count = %d\n", total); // mostra total         // espera thread 'verifya<'
  return 0;
}