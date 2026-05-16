#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int n = strtol(argv[2], NULL, 10);
    int fd = open(argv[1], O_RDWR);
    long long total_size = 0;

    for (int i = 0; i < n; ++i) {
        long long cur = 0;
        int offset = sizeof(cur);

        if (lseek(fd, -offset * (i + 1), SEEK_END) < 0) {
            break;
        }

        read(fd, &cur, sizeof(cur));
        total_size += cur;
    }

    int offset = sizeof(total_size);
    lseek(fd, -offset, SEEK_END);
    write(fd, &total_size, sizeof(total_size));

    close(fd);

    return 0;
}