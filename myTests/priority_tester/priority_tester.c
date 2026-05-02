#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t child_pid = -1;

void handle_sigint(int sig) {
    if (child_pid > 0) {
        kill(child_pid, SIGKILL);
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <executable>\n", argv[0]);
        return 1;
    }

    signal(SIGINT, handle_sigint);

    child_pid = fork();

    if (child_pid < 0) {
        printf("Fork failed\n");
        return 1;
    } else if (child_pid == 0) {
        execvp(argv[1], &argv[1]);

        printf("Child process failed to execute\n");
        exit(1);
    } else {
        char proc_path[64];
        sprintf(proc_path, "/proc/%d/psinfo", child_pid);

        for (int t = 0; t <= 30; t++) {

            int status;
            if (waitpid(child_pid, &status, WNOHANG) == child_pid) break;

            FILE *f = fopen(proc_path, "r");
            if (f != NULL) {
                int version, endpoint, blocked_on, priority;
                char type, state;
                char name[256];

                int readed = fscanf(f, "%d %c %d %s %c %d %d", &version, &type, &endpoint, name, &state,  &blocked_on, &priority);

                if (readed == 7) {
                    printf("%d,%d\n", t, priority);
                    fflush(stdout);
                }
                fclose(f);
            }
            sleep(1);
        }
        kill(child_pid, SIGKILL);
        waitpid(child_pid, NULL, 0);
    }

    return 0;
}