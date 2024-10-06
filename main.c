#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 30

char forest[SIZE][SIZE];
pthread_mutex_t forest_mutex[SIZE][SIZE];

void *sensor_thread(void *arg);
void *fire_generator(void *arg);
void *control_center(void *arg);

int main() {
    pthread_t sensors[SIZE][SIZE], fire_thread, control_thread;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            forest[i][j] = '-';
            pthread_mutex_init(&forest_mutex[i][j], NULL);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            pthread_create(&sensors[i][j], NULL, sensor_thread, (void*)(size_t)(i * SIZE + j));
        }
    }

    pthread_create(&fire_thread, NULL, fire_generator, NULL);

    pthread_create(&control_thread, NULL, control_center, NULL);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            pthread_join(sensors[i][j], NULL);
        }
    }
    pthread_join(fire_thread, NULL);
    pthread_join(control_thread, NULL);

    return 0;
}
