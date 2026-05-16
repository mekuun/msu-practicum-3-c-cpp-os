#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#define GRANDSON 2
#define SON 1
#define DAD 0

int new(int id, int cnt, const char *my_id, int *fd)
{
    write(fd[1], &cnt, sizeof(int));
    int next = (id + cnt) % 3;
    if (next == id) next = (next + 2) % 3;
    printf("%s %d %d\n", my_id, cnt, next);
    fflush(stdout);
    return next;
}

int main()
{
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    };
    unsigned short arr[3]={0, 0, 0};
    union semun arg; arg.array=arr;

    int fd[2];
    if (pipe(fd) == -1) {perror("Pipe error"); return 1;}

    int file;
    if ((file = open("MZ14.txt", O_CREAT | O_TRUNC, 0666)) == -1) {fprintf(stderr, "File() problem\n"); return 1;}
    close(file);

    key_t key = ftok("MZ14.txt", 5);

    int semid = semget(key, 3, IPC_CREAT | 0666);

    struct sembuf block_dad = {0, -1, 0}, block_son = {1, -1, 0}, block_grandson = {2, -1, 0},
            unblock_dad = {0, 1, 0}, unblock_son = {1, 1, 0}, unblock_grandson = {2, 1, 0};

    semctl(semid, 0, SETALL, arg);

    pid_t son, grandson;

    int n, cnt=0;
    scanf("%d", &n);

    if ((son = fork()) == -1) {perror("Fork error"); return 1;}
    if (son == 0) {
        if ((grandson = fork()) == -1) {perror("Fork error"); return 1;}
        if (grandson == 0) { // внучок
            while (cnt < n) {
                semop(semid, &block_grandson, 1);
                read(fd[0], &cnt, sizeof(int));
                cnt++;
                if (cnt < n){
                    if (new(GRANDSON, cnt, "grandson", fd) == SON) semop(semid, &unblock_son, 1); else semop(semid, &unblock_dad, 1);
                }
                else if (cnt == n) {
                    new(GRANDSON, cnt, "grandson", fd);
                    write(fd[1], &cnt, sizeof(int));
                    semop(semid, &unblock_dad, 1);
                    semop(semid, &unblock_son, 1);
                }
            }
            close(fd[0]);close(fd[1]);
            semctl(semid, 0, IPC_RMID);
            return 0;
        }
        else { // сын
            while (cnt < n) {
                semop(semid, &block_son, 1);
                read(fd[0], &cnt, sizeof(int));
                cnt++;
                if (cnt < n) {
                    if (new(SON, cnt, "son", fd) == DAD) semop(semid, &unblock_dad, 1); else semop(semid, &unblock_grandson, 1);
                }
                else if (cnt == n) {
                    new(SON, cnt, "son", fd);
                    write(fd[1], &cnt, sizeof(int));
                    semop(semid, &unblock_dad, 1);
                    semop(semid, &unblock_grandson, 1);
                }
            }
            wait(NULL);
            close(fd[0]);close(fd[1]);
            semctl(semid, 0, IPC_RMID);
            return 0;
        }
    }
    else { // отец
        write(fd[1], &cnt, sizeof(int));
        semop(semid, &unblock_grandson, 1);
        while (cnt < n) {
            semop(semid, &block_dad, 1);
            read(fd[0], &cnt, sizeof(int));
            cnt++;
            if (cnt < n) {
                if (new(DAD, cnt, "father", fd) == SON) semop(semid, &unblock_son, 1); else semop(semid, &unblock_grandson, 1);
            }
            else if (cnt == n) {
                new(DAD, cnt, "father", fd);
                write(fd[1], &cnt, sizeof(int));
                semop(semid, &unblock_son, 1);
                semop(semid, &unblock_grandson, 1);
            }
        }
        wait(NULL);
        close(fd[0]); close(fd[1]);
        semctl(semid, 0, IPC_RMID);
        return 0;
    }
}