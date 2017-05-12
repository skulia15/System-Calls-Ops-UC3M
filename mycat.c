#include <stdio.h>		/* Header file for printf */
#include <sys/types.h>		/* Header file for system call  open */
#include <sys/stat.h>
#include <stdlib.h> /*for handling warnings for use of malloc */
#include <fcntl.h>
#include <unistd.h>		/* Header file for system calls read, write y close */

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	/*If the number of arguments is less than two (argv[0] -> program, argv[|] -> file to be shown) we print the error and return -1*/
	if(argc < 2){
		printf("Not enough arguments\n");
		return -1;
	}

	//Create and allocate a buffer of size 1024b
	char * myBuffer;
    myBuffer = (char*) malloc (BUFFER_SIZE);
    if (myBuffer == NULL){
        printf("Failed to allocate buffer\n");
        return -1;
    }

    //Open file to be read, returns a file descriptor
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0){
        printf("Error opening file\n");
        return -1;
    }

    //Read the contents of the file to the buffer
    if(read(fd, myBuffer, BUFFER_SIZE) < 0){
        printf("Failed to read data\n");
        return -1;
    }

    //Write the contents of the buffer to standard output
    if (write(STDOUT_FILENO, myBuffer, BUFFER_SIZE) < 0){
        printf("Failed to write data\n");
        return -1;
    }

    //Close the file descriptor
    if(close(fd) != 0){
        printf("Failed to close file descriptor\n");
        return -1;
    }

	return 0;
}

