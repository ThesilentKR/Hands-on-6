#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* print_message_function(void* thread_id) {
    long tid = (long)thread_id;
    printf("Hilo %ld está en ejecución.\n", tid);
    sleep(2);
    printf("Hilo %ld ha terminado.\n", tid);
    pthread_exit(NULL);
}

int main() {
    const int NUM_THREADS = 5;
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creando el hilo %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message_function, (void*)t);   
        if (rc) {
            fprintf(stderr, "Error: No se pudo crear el hilo %ld, código de error %d\n", t, rc);
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("Todos los hilos han terminado.\n");
    return 0;
}