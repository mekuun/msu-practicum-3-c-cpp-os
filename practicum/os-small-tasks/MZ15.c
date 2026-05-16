l
enum classes{CLASS_A = 0x0, CLASS_B = 0x2, CLASS_C = 0x6};
enum class_offsets{OFFS_A = 31, OFFS_B = 30, OFFS_C = 29};
enum net_offsets{NET_A = 24, NET_B = 16, NET_C = 8};


struct msgbuf{
    long mtype;
    unsigned int addr;
    int last;
};


int main(){

    struct msgbuf message;
    int f;
    if ((f = open("helpme.txt", O_CREAT | O_TRUNC, 0666)) == -1) {fprintf(stderr, "File() problem\n"); return 1;}
    close(f);

    key_t key = ftok("helpme.txt", 52);
    if (!key) {perror("I HATE IPC"); return 1;}

    int msgid = msgget(key, IPC_CREAT | 0666);
    if (!msgid) {fprintf(stderr, "Msgget() problem\n"); return 1;}

    int a[4];
    unsigned int res = 0;

    if (!fork()) { //
        msgrcv(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 1, 0);
        while (message.last != 1){
            fprintf(stdout, "A %x \n", message.addr);
            fflush(stdout);
            message.mtype = 4;
            msgsnd(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 0);
            msgrcv(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 1, 0);
        }
        return 0;
    }

    if (!fork()){ //Ð¼Ñ‹ Ð² Ð´Ð¾Ñ‡ÐµÑ€Ð¸ B
        msgrcv(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 2, 0);
        while (message.last != 1){
            fprintf(stdout, "B %x \n", message.addr);
            fflush(stdout);
            message.mtype = 4;
            msgsnd(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 0);
            msgrcv(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 2, 0);
        }
        return 0;
    }

    if (!fork()){
        msgrcv(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 3, 0);
        while (message.last != 1){
            fprintf(stdout, "C %x \n", message.addr);
            fflush(stdout);
            message.mtype = 4;
            msgsnd(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 0);
            msgrcv(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 3, 0);
        }
        return 0;
    }


    while (fscanf(stdin,"%d.%d.%d.%d\n", &a[0],  &a[1], &a[2], &a[3]) == 4){
        res = 0xFFFFFFFF;
        for (int i = 0; i < 4; i++) {
            res &= 0xFFFFFF00;
            res |= (a[i]);
            if (i < 3) res <<= 8;
        }
        if ((res >> OFFS_C) == CLASS_C) {message.mtype = 3; message.addr = (res << (32 - OFFS_C)) >> (NET_C + 32 - OFFS_C);}
        else if ((res >> OFFS_B) == CLASS_B) {message.mtype = 2; message.addr = (res << (32 - OFFS_B)) >> (NET_B + 32 - OFFS_B);}
        else if ((res >> OFFS_A) == CLASS_A) {message.mtype = 1; message.addr = (res << (32 - OFFS_A)) >> (NET_A + 32 - OFFS_A);}
        msgsnd(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 0);
        msgrcv(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 4, 0);
    }



    message.addr = 0;
    message.mtype = 1;
    msgsnd(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 0);
    message.mtype = 2;
    msgsnd(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 0);
    message.mtype = 3;
    msgsnd(msgid, &message, sizeof(struct msgbuf) - sizeof(long int), 0);

    wait(NULL);
    wait(NULL);
    wait(NULL);
    return 0;
}