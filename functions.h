#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void *sensor_thread(void *arg);
void *fire_generator(void *arg);
void *control_center(void *arg);
void communicate_with_neighbors(int x, int y);

#endif
