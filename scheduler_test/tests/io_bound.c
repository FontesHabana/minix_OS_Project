/*
* Name: io_bound.c
 * Expected Behavior:
 * This process is categorized as I/O-bound or interactive because it frequently
 * yields the processor before its quantum expires. The scheduler should
 * recognize the frequent voluntary blocking and maintain the process at a
 * high-priority level (low numeric value) to ensure high responsiveness
 * when the process wakes up.
 */
#include <unistd.h>

int main () {

    while (1) {
        sleep(1);
    }
    return 0;
}