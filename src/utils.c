// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "../include/rebootx.h"

void log_action(const char *msg) {
    FILE *f = fopen("/var/log/rebootx.log", "a");
    if (!f) return;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm);
    fprintf(f, "[%s] %s\n", buf, msg);
    fclose(f);
}

void send_msg(const char *msg) {
    if (!msg) return;
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "wall \"%s\"", msg);
    int ret = system(cmd);
    if (ret == -1) {
        perror("system failed");
    } else if (WIFEXITED(ret) && WEXITSTATUS(ret) != 0) {
          fprintf(stderr, "Command failed with exit code %d\n", WEXITSTATUS(ret));
    }
}

void delay_reboot(int sec) {
    for (int i = sec; i > 0; i--) {
        printf("\rRebooting in %d seconds...", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}
