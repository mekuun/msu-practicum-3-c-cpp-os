#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun {
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    ushort *array;         /* used for GETALL and SETALL */
};

struct sembuf block_father={0, -1, 0},
        unblock_father={0, 1, 0},
        block_son={1, -1, 0},
        unblock_son={1, 1, 0},
        block_grandson={2, -1, 0},
        unblock_grandson={2, 1, 0};

struct sembuf *blocks[3] = {&block_father, &block_son, &block_grandson};
struct sembuf *unblocks[3]={&unblock_father, &unblock_son, &unblock_grandson};
int n, fd[2], semid;

char do_work(char *str, int *cnt, int ID){
    int next;
    read(fd[0], cnt, sizeof(int));
    (*cnt)++;
    if (*cnt > n){
        write(fd[1], cnt, sizeof(int));
        write(fd[1], cnt, sizeof(int));
        switch(ID){
            case 0:
                semop(semid, &unblock_son, 1);
                semop(semid, &unblock_grandson, 1);
                break;
            case 1:
                semop(semid, &unblock_father, 1);
                semop(semid, &unblock_grandson, 1);
                break;
            case 2:
                semop(semid, &unblock_father, 1);
                semop(semid, &unblock_son, 1);
                break;
        }
        return 1;
    }
    next=( ID + ( * cnt ) ) % 3;
    if (next == ID) next = (next + 2 ) % 3;



    printf("%s %d %d\n", str, *cnt, next);
    fflush(stdout);

    write(fd[1], cnt, sizeof(int));
    semop(semid, unblocks[next], 1);
    semop(semid, blocks[ID], 1);
    return 0;
}

int main(){
    key_t key=ftok("/", '1');
    semid=semget(key, 3, 0666|IPC_CREAT);
    scanf("%d", &n);


    ushort arr[3]={0, 0, 0};

    union semun arg; arg.array=arr;
    semctl(semid, 0, SETALL, arg);

    int res, cnt=0;

    if (pipe(fd)==-1) {
        perror("mz14: Pipe error"); exit(1);
    }


    if ((res=fork())>0){
        semop(semid, &block_father, 1);

        while (do_work("father", &cnt, 0)!=1){
        };

        wait(NULL);
        close(fd[0]); close(fd[1]);
        semctl(semid, 0, IPC_RMID);

    }
    else if (res==0){
        if ((res=fork())>0){
            write(fd[1], &cnt, sizeof(int));
            semop(semid, &unblock_grandson, 1);
            semop(semid, &block_son, 1);

            while (do_work("son", &cnt, 1)!=1);

            wait(NULL);
            close(fd[0]); close(fd[1]);
            semctl(semid, 0, IPC_RMID);

        }
        else if (res==0){
            semop(semid, &block_grandson, 1);

            while (do_work("grandson", &cnt, 2) != 1) {
            }

            close(fd[0]); close(fd[1]);
            semctl(semid, 0, IPC_RMID);
        }
    }
    return 0;
}