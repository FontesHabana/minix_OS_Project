
/*
 * Name: mixed_burst.c
 * Expected Behavior:
 * This workload simulates a hybrid behavior by alternating between intensive
 * computation and voluntary yielding. The expected result is a dynamic
 * priority profile: the priority should drop during the CPU-intensive burst
 * and stabilize or recover during the sleep phase, depending on the kernel's
 * priority-boosting policy.
 */


#include <unistd.h>
#include <stdio.h>

int main() {
    while (1) {
        for (int i = 1; i <= 1000000000; i++);
        sleep(2);
    }
}