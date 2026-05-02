/*
* Name: cpu_bound.c
 * Expected Behavior:
 * This process is strictly CPU-bound. Under a Multi-Level Feedback Queue (MLFQ)
 * scheduler, the process is expected to consume its full time quantum in every
 * execution cycle. Consequently, the scheduler should trigger a priority
 * degradation, systematically moving the process to lower-priority queues
 * (higher numeric values) over time.
 */
#include <stdio.h>

int main() {
    unsigned long long a=0;

    while (1) {
        a++;
    }
return 0;
}
