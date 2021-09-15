#include "virtual-sensor.h"
#include <stdlib.h>

float random_value(float max, float min){
    float scale = rand()/(float) RAND_MAX;
    return min + scale *(max*min);
}

float read_tempature(){
    return random_value(0, 35);
}

float read_humidity(){
     return random_value(50, 80);
}