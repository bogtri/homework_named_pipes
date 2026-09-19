#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

static bool process_cmd(const char *cmd)
{
    bool stop = false;

    if (strcmp(cmd, "PING") == 0)
    {
        printf("[SERVER] PONG\n");
    }
    else if (strcmp(cmd, "STOP") == 0)
    {
        printf("[SERVER] Stopping...\n");
        stop = true;
    }
    else
    {
        printf("[SERVER] Unsupported command\n");
    }

    return stop;
}

int main()
{
    const char *path = "/tmp/telemetry.fifo";
    int fd;
    char cmd[10];
    bool stop = false;

    if (mkfifo(path, 0666) == -1)
    {
        printf("Cannot open a pipe\n");
        return 1;
    }

    printf("[SERVER] Listening on %s...\n", path);

    while (1)
    {
        fd = open(path, O_RDONLY);

        if (fd == -1)
        {
            printf("Cannot open a pipe\n");
            unlink(path);
            return 1;
        }

        if (read(fd, cmd, sizeof(cmd)) == -1)
        {
            printf("[SERVER] Error reading data from pipe\n");
        }
        else
        {
            stop = process_cmd(cmd);
        }

        close(fd);

        if (stop)
        {     
            unlink(path);
            return 0;
        }
    }

    return 0;
}