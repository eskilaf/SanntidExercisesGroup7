// Compile with `gcc foo.c -Wall -std=gnu99 -lpthread`, or use the makefile
// The executable will be named `foo` if you use the makefile, or `a.out` if you use gcc directly

#include <pthread.h>
#include <stdio.h>

int i = 0;
void* ptr_i = &i;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

// Note the return type: void*
void* incrementingThreadFunction(void* k){
    // TODO: increment i 1_000_000 times
    for (int j = 0; j < 1000000; j++) {
        pthread_mutex_lock(&mutex);
        int* temp_ptr = (int*)k;
        *temp_ptr = *temp_ptr + 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* decrementingThreadFunction(void* k){
    // TODO: decrement i 1_000_000 times
    for (int j = 0; j < 999998; j++) {
        pthread_mutex_lock(&mutex);
        int* temp_ptr = (int*)k;
        *temp_ptr = *temp_ptr - 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(){
    // TODO: 
    // start the two functions as their own threads using `pthread_create`
    // Hint: search the web! Maybe try "pthread_create example"?

    pthread_t t1, t2;


    pthread_create(&t1, NULL, incrementingThreadFunction, (void*) ptr_i);
    pthread_create(&t2, NULL, decrementingThreadFunction, (void*) ptr_i);


    // TODO:
    // wait for the two threads to be done before printing the final result
    // Hint: Use `pthread_join`    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("The magic number is: %d\n", i);
    return 0;
}
