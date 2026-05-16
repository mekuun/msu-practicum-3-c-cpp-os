#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>


int main(int argc, char** argv) {
    int disk = open(argv[1], O_RDONLY);
    unsigned short tline, vaddr, result, table;
    sscanf(argv[2], "%hx", &table);
    while (scanf("%hx", &vaddr) == 1) {
        lseek(disk, table, SEEK_SET);
        lseek(disk, (vaddr>>9) * 2, SEEK_CUR);
        read(disk, &tline, 2);
        vaddr = vaddr << 7;
        vaddr = vaddr >> 7;
        tline = tline | vaddr;
        lseek(disk, tline, SEEK_SET);
        read(disk, &result, 2);
        printf("%u\n", result);
    }
    return 0;
}