#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    time_t start = time(NULL);
    time_t current;

    while ((current = time(NULL)) - start < 12) {
        volatile long long int dummy = 0;
        for (int i = 0; i < 1000; i++) {
            dummy += i * i;
        }
    }
    while ((current = time(NULL)) - start < 35) {
        usleep(50000); 
    }

    return 0;
}