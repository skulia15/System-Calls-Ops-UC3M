#include <stdio.h>		/* Header file for system call printf */
#include <unistd.h>		/* Header file for system call gtcwd */
#include <sys/types.h>		/* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
    DIR * dirPointer; //a pointer to an opened directory
    struct dirent * entry; //a pointer to an entry in the opened directory
    char myBuffer[PATH_MAX]; //a buffer that stores the path to the current working directory

    //If we want to list the current working directory, that is if no arguments are provided
    if(argc == 1){
		dirPointer = opendir(getcwd(myBuffer, PATH_MAX));//get the cwd and store it in the buffer and then open that directory and store it in the dirPointer
	}

    //If we want to list a specific directory, given an argument
    //if more are given, open the first one given.
    else if(argc >= 2){
		dirPointer = opendir(argv[1]);
	}

    //Error handling for opening directories
    if(dirPointer == NULL){
        printf("Error opening the directory\n");
        return -1;
    }

    //Create a directory entry using readdir, print the name and then loop through all entries in the directory
    entry = readdir(dirPointer);
    while (entry != NULL){
        printf("%s\n", entry->d_name);
        entry = readdir(dirPointer);
    }

    //close the directory descriptor
    if (closedir(dirPointer) < 0){
        printf("Error closing the directory");
        return -1;
    }

	return 0;
}

