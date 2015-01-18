#include <stdio.h>
#include "Random.h"

int random(int MAX_SIZE) {
   return rand()%MAX_SIZE;
}