#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

static bool is_command_valid(const char *cmd) {
    return strcmp(cmd, "PING") == 0 || strcmp(cmd, "STOP") == 0;
}

int main(int argc, char *argv[])
{
    const char *path = "/tmp/telemetry.fifo";
    int fd;

    if (argc != 2) {
        printf("[CLIENT] Expected 1 argument\n");
        return 1;
    }

    const char *cmd = argv[1];

    if (!is_command_valid(cmd)) {
        printf("[CLIENT] Unsupported command\n");
        return 1;
    }

    fd = open(path, O_WRONLY);

    if (fd == -1) {
        printf("[CLIENT] Cannot open a pipe\n");
        return 1;
    }

    if (write(fd, cmd, strlen(cmd) + 1) == -1) {
        printf("[CLIENT] Error writing to a pipe\n");
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}