#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define ERRBREAK(s) do { fprintf(stderr, "%s\n", s); exit(1); } while(0)

int word_length(int fd, off_t offset){
    lseek(fd, offset - 1, SEEK_SET);
    char a = ';', count = 0;
    do {
        count ++;
        if (read(fd, &a, 1) == 0) break;
    } while ((a != ' ') && (a != ',') && (a != '.') && (a != '\n'));
    count -= 1;
    return count;
}

int word_change(int fd, off_t offset, int fl, int num,  char new_l){
    char tmp = '*';
    char *fath = "FATHER", *son = "SON";
    lseek(fd, offset, SEEK_SET);
    write(fd, &tmp, sizeof(char));
    tmp = new_l;
    write(fd, &tmp, sizeof(char));
    //If n is equal to 0, it is the father
    if (num == 0){
        lseek(fd, offset + fl - 6, SEEK_SET);
        write(fd, fath, 6);
        return 0;
    }
    lseek(fd, offset + fl - 1, SEEK_SET);
    while (num != 0){
        tmp = (num % 10) + '0';
        num /= 10;
        write(fd, &tmp, 1);
        lseek(fd, -2, SEEK_CUR);
    }
    lseek(fd, -2, SEEK_CUR);
    write(fd, son, 3);
    return 0;
}

int text_processing(int fin, int proc_num, char old_l, char new_l){
    char curr_char = ' '; int flag = 1, k = 1, offset;
    while(k == 1){
        if ((curr_char != ' ') && (curr_char != ',') && (curr_char != '.') && (curr_char != '\n') && flag && (curr_char == old_l)) {
            offset = lseek(fin, 0, SEEK_CUR);
            int wl = (word_length(fin, lseek(fin, 0, SEEK_CUR)));
            lseek(fin, offset - 1, SEEK_SET);
            if (wl >= 9) {
                word_change(fin, offset - 1, wl, proc_num, new_l);
            }
            lseek(fin, offset - 1, SEEK_SET);
            flag = 0;
        }
        else if ((curr_char != ' ') && (curr_char != ',') && (curr_char != '.') && (curr_char != '\n') && (curr_char != old_l)) flag = 0;
        else if ((curr_char == ' ') || (curr_char == ',') || (curr_char == '.') || (curr_char == '\n')) flag = 1;
        k = read(fin, &curr_char, 1);
    }
    lseek(fin, 0, SEEK_SET);
    return 0;
}


int main(int argc, char **argv) {
    if (argc < 3) ERRBREAK("Unknown errors");
    long N = strtol(argv[2], NULL, 10);
    int i, j;
    for (i = 3; i <= argc - 1; ++i) {
        if (i % 2 == 1) {
            for (j = i + 2; j <= argc - 1; ++j) {
                if (j % 2 == 1) {
                    if (!strcmp(argv[i], argv[j])) ERRBREAK("Incorrect rules");
                }
            }
        }
        if (!strcmp(argv[i], "*")) ERRBREAK("Incorrect rules");
    }

    if ((N == 0) && (argv[2][0] != '0')) ERRBREAK("Unknown errors");
    if (argc != (3 + N * 2)) ERRBREAK("Wrong number of process");
    int fin = open(argv[1], O_RDWR);
    if (fin == -1) ERRBREAK("Can't open file");


    text_processing(fin, 0, argv[3][0], argv[3 + 1][0]); //pu pu pu
    close(fin);
    for (i = 2; i < 2 * N ; i += 2){
        if (fork() == 0){  // mi v sine
            int fin = open(argv[1], O_RDWR);
            char old = argv[3 + i][0], new = argv[3 + i + 1][0];
            lseek(fin, 0, SEEK_SET);
            text_processing(fin, i/2, old, new); //pu pu pu
            lseek(fin, 0, SEEK_SET);
            close(fin);
            exit(0);
        }
    }
    for (i = 2; i < 2 * N ; i += 2){wait(NULL);}

    return 0;
}

