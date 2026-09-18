#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Expected 1 argument\n");
        return 1;
    }
    const char *cmd = argv[1];
    if (strcmp(cmd, "PING") != 0 && strcmp(cmd, "STOP") != 0) {
        printf("Unsupported command\n");
        return 1;
    }
    const char *path = "/tmp/telemetry.fifo";
    int fd;
    fd = open(path, O_WRONLY);
    if (fd == -1) {
        printf("Cannot open a pipe\n");
        return 1;
    }
    if (write(fd, cmd, strlen(cmd) + 1) == -1) {
        printf("Error writing to a pipe\n");
        close(fd);
        return 1;
    }
    close(fd);
    return 0;
}