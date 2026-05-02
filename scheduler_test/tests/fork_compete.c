/*
* Name: fork_compete.c
 * Expected Behavior:
 * This test evaluates scheduler fairness and the handling of process
 * multiplication. As multiple CPU-intensive processes compete for the same
 * resources, all spawned children (and the parent) should exhibit a
 * simultaneous decay in priority, eventually settling into the lowest
 * priority tiers of the system.
 */

#include <unistd.h>
#include <sys/types.h>

int main() {
    for(int i = 0; i < 3; i++) {
        if(fork() == 0) {
            while(1);
        }
    }
    while(1);
    return 0;
}