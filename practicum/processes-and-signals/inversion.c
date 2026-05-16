#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>


int main(int argc, char **argv){
	int first, second;

	int finp = open(argv[1], O_RDWR);
	lseek(finp, 0, SEEK_SET);
	int file_length = lseek(finp, 0, SEEK_END)/(sizeof(int)); // длина файла в байтах
	
	for (int i = 0; i < (file_length/2) + (file_length%2); i ++){
		lseek(finp, i * sizeof(int), SEEK_SET);
		read(finp, &first, sizeof(int));
		lseek(finp, -(i + 1) * sizeof(int), SEEK_END);
		read(finp, &second, sizeof(int));
		//printf("%x %x\n", first, second); fflush(stdout);
		lseek(finp, i * sizeof(int), SEEK_SET);
		write(finp, &second, sizeof(int));
		lseek(finp, -(i + 1) * sizeof(int), SEEK_END);
		write(finp,&first, sizeof(int));

	}
}
