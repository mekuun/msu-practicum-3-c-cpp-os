#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>
#include <sys/stat.h>

int main(int argc, char **argv){

    int k = 0, n = 0;
    int finp, fout;
    char buf;
    char chbuf;
    struct stat sb;

    if (argc != 3){
        fprintf(stderr, "Error");
        return 1;
    }

    finp = open(argv[1], O_RDONLY);
    if (finp == -1){
        perror("OUTPUT FILE OPEN ERROR");
        return 1;
    }
    fstat(finp, &sb);

    fout = open(argv[2], O_CREAT | O_WRONLY, sb.st_mode);
    if (fout == -1){
        perror("INPUT FILE OPEN ERROR");
        return 1;
    }


    while ((n = read(finp, &buf, sizeof(char))) > 0){
        if (isalpha(buf)){
            write(fout, &buf, 1);
            k ++;
        }

        else if (k == 0){
            write(fout, &buf, 1);
        }

        else {
            if (k >= 10){
                chbuf = k / 10 + '0';
                write (fout, &chbuf, sizeof(char));

                chbuf  = k % 10 + '0';
                write (fout, &chbuf, sizeof(char));
            }
            else{
                chbuf = k + '0';
                write (fout, &chbuf, sizeof(char));
            }
            k = 0;
            write(fout, &buf, sizeof(char));
        }
    }

    close(fout);
    close(finp);

    return 0;
}