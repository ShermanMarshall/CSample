#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

//Function to be executed in a separate thread
void func(void* arg) {
	//Cast of one-argument paramater from pthread_create
	pthread_mutex_t* mutext = (pthread_mutex_t*) arg;

	//Attempt to lock the mutext, blocking until successful
	pthread_mutex_lock(mutext);

	printf("test\n");
	//busy work to distinguish results
	for (int x = 0; x < 33000; x++) { }

	printf("done\n");
}

int main() {
	//Pointer to mutex type
	pthread_mutex_t * mutex;

	//initialize mutex structure
	int num = pthread_mutex_init(mutex, NULL);
	if (num != 0) {
		printf("Error acquiring the mutext\n");
		return 0;
	}

	//lock the mutex and return the result (0 or > 0)
	num = pthread_mutex_lock(mutex);
	if (num != 0) {
		printf("Error at mutex locking: %i\n", num);
	}

	//declare pthreads
	pthread_t thread;//, thread2;

	//pthread_create executes functions in a separate thread
	pthread_create(&thread, NULL, &func, mutex);
	//pthread_create(&thread2, NULL, &func, mutex);

	//busy work
	for (int x = 0; x < 10000000; x++) { }

	//Remove the lock, making it accessible to other threads
	pthread_mutex_unlock(mutex);

	printf("%i\n", num);
	for (int x = 0; x < 10000000; x++) { }
}
