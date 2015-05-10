#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("usage: %s fromfile tofile\n", argv[0]);
    }

    time_t pre_time = time(NULL);

    FILE *fp = NULL;
    char buf[4096];
    if ((fp = fopen(argv[1], "r+")) == NULL) {
        perror("fopen");
        goto error;
    }

    int fd = 0;
    if ((fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC)) < 0) {
        perror("open");
        goto error;
    }
    
    while (fgets(buf, 4096, fp)) {
        write(fd, buf, strlen(buf));
    }

    printf("time used: %d\n", (int) (time(NULL) - pre_time));
    fclose(fp);
    close(fd);
    return 0;

error:
    if (!fp) {
        fclose(fp);
    }
    if(!fd) {
        close(fd);
    }

    exit(-1);
}
