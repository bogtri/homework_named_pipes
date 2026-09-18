#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    const char *path = "/tmp/telemetry.fifo";
    if (mkfifo(path, 0666) == -1) {
        printf("Cannot open a pipe\n");
        return 1;
    }
    printf("[SERVER] Listening on %s...\n", path);
    int fd;
    char s[10];
    while (1)
    {
        fd = open(path, O_RDONLY);
        read(fd, s, sizeof(s));
        if (strcmp(s, "PING") == 0) {
            printf("[SERVER] PONG\n");
        } else if (strcmp(s, "STOP") == 0) {
            printf("[SERVER] Stopping...\n");
            close(fd);
            unlink(path);
            return 0;
        } else {
            printf("[SERVER] Unsupported command\n");
        }       
        close(fd);
    }
    return 0;
}