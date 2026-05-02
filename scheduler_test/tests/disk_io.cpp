/*
* Name: disk_io.c
 * Expected Behavior:
 * This process performs frequent synchronous disk operations. It tests how the
 * scheduler handles processes blocked on hardware I/O rather than simple timers.
 * The process is expected to retain a higher priority than pure CPU-bound tasks,
 * as the kernel typically rewards processes that are waiting for slow
 * peripheral devices to complete their tasks.
 */

#include <stdio.h>

int main() {
    FILE *f;
    while (1) {
       f= fopen("temp.txt", "w");
        for (int i = 1; i <= 500; i++) {
            fprintf(f, "Write data : %d\n", i);
        }
        fclose(f);
    }
}