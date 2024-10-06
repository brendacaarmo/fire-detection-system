#include "functions.h"

extern char forest[SIZE][SIZE];
extern pthread_mutex_t forest_mutex[SIZE][SIZE];

void *sensor_thread(void *arg) {
    int id = (int)(size_t)arg;
    int x = id / SIZE;
    int y = id % SIZE;

    while (1) {
        pthread_mutex_lock(&forest_mutex[x][y]);
        if (forest[x][y] == '@') {
            communicate_with_neighbors(x, y);
        }
        pthread_mutex_unlock(&forest_mutex[x][y]);
        usleep(100000);
    }
    return NULL;
}

void communicate_with_neighbors(int x, int y) {
}

void *fire_generator(void *arg) {
    while (1) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        pthread_mutex_lock(&forest_mutex[x][y]);
        if (forest[x][y] == '-') {
            forest[x][y] = '@';
        }
        pthread_mutex_unlock(&forest_mutex[x][y]);

        sleep(3); 
    }
    return NULL;
}

void *control_center(void *arg) {
}
