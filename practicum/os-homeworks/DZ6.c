#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
volatile sig_atomic_t flag_no_error = 1;
void handler(int s)
{
    flag_no_error = 0;
}

enum parse_results{PALKA = 3, EOFile = 2};

int parse_word(char **ptr) {
    int size, curr_char, single_quotes_flag = 0, double_quotes_flag = 0;
    char *buf, *curr_word;
    curr_char = getchar();
    while (curr_char == ' ')
        curr_char = getchar();
    if (curr_char == '|') return PALKA;
    if (curr_char == '\n') return EOFile;
    size = 8;

    curr_word = (char*)malloc(size*sizeof(char));
    if (!curr_word) {perror("Memory allocation error"); exit(1);}
    if (curr_char == '\'') {
        single_quotes_flag = 1;
        curr_char = getchar();
    } else if (curr_char == '\"') {
        double_quotes_flag = 1;
        curr_char = getchar();
    }

    int i =0;
    while ((curr_char != ' ' || (single_quotes_flag == 1) || (double_quotes_flag == 1)) && curr_char != '\n' && curr_char != '|') {
        if (curr_char == '\''){
            if (single_quotes_flag == 1){
                single_quotes_flag -= 1;
                break;
            }
            else{
                free(curr_word);
                fprintf(stderr, "Syntax error\n");
                exit(1);
            }
        }
        if (curr_char == '\"'){
            if (double_quotes_flag == 1){
                double_quotes_flag -= 1;
                break;
            }
            else{
                free(curr_word);
                fprintf(stderr, "Syntax error\n");
                exit(1);
            }
        }
        if (size - 1 == i) {
            size *= 2;
            buf = (char*)realloc(curr_word,size*sizeof(char));
            if (!buf) {
                free(curr_word);
                perror("Memory reallocation error");
                exit(1);
            }
            curr_word = buf;
        }
        curr_word[i] = curr_char;
        i++;
        curr_char = getchar();
    }

    if (curr_char == '|' || curr_char == '\n') ungetc(curr_char, stdin);
    if (single_quotes_flag + double_quotes_flag >= 1) {
        fprintf(stderr, "Syntax error\n");
        exit(1);
    }
    curr_word[i] = 0;
    *ptr = curr_word;
    return 0;
}


int main() {
    int i = 0, res, previous = -1, size = 8, pcount = 1, fd[2], io[] = {0, 1};
    int status;
    char **word_count = (char **) malloc(sizeof(char *) * size), **buf, **ptr;

    if (!word_count) {
        free(word_count);
        perror("Memory allocation error");
        exit(1);
    }

    while ((res = parse_word(word_count + i)) != EOFile) { //eof
        if ((previous == PALKA || previous == -1) && res == PALKA) {
            fprintf(stderr, "Syntax error\n");
            exit(1);
        }

        if (word_count[i] == NULL) pcount++;
        i++;

        if (i == size - 1) {
            size *= 2;
            buf = (char **) realloc(word_count, size * sizeof(char *));
            if (!buf) {
                free(word_count);
                perror("Memory reallocation error");
                exit(1);
            }
            word_count = buf;
        }
        previous = res;
    }

    if (previous == PALKA) {
        fprintf(stderr, "Syntax error \n");
        return 1;
    }

    ptr = word_count;
    pid_t son_id;

    int input = 0;
    char flag_error = 0;

    ptr = word_count;
    signal(SIGUSR1, handler);

    for (i = 0; i < pcount; i++) {
        pipe(fd);
        son_id = fork();
        if (son_id == -1) {
            free(word_count), perror("Fork error");
            return 1;
        }
        if (son_id == 0) {
            dup2(fd[1], 1);
            if (i != 0) dup2(input, 0);
            close(fd[0]); close(fd[1]);
            execvp(ptr[0], ptr);
            fprintf(stderr, "Command %s not found\n", ptr[0]);
            fflush(stderr);
            kill(getppid(), SIGUSR1);
            return 1;
        }
        close(fd[1]);
        input = fd[0];

        while (*ptr != NULL) ptr++;
        ptr++;
    }
    while(wait(NULL) != -1);
    char c;
    if (flag_no_error) {while(read(input, &c, sizeof(char)) == 1) printf("%c", c);}
    if (flag_no_error) printf("\n");
    return 0;
}