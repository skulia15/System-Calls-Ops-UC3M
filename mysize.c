#include <stdio.h>	/*Header file for system call printf*/
#include <sys/types.h>	/*Header file for system call fstat*/
#include <sys/stat.h>
#include <stdlib.h> /*for handling warnings for use of malloc */
#include <fcntl.h>	/*Header file for system call fcntl*/
#include <dirent.h> 	/*Header file for system call opendir, closedir,readdir...*/
#include <unistd.h>

int main(int argc, char *argv[])
{
	DIR * dirPointer; //a pointer to an opened directory
    struct dirent * entry; //a pointer to an entry in the opened directory
    char pathBuf[PATH_MAX]; //a buffer that stores the path to the current working directory
    int fd; //the file descriptor
    int mySize; //the size of the specified file

    //Get current working directory and open it
    dirPointer = opendir(getcwd(pathBuf, PATH_MAX));
    if(dirPointer == NULL){
        printf("Error opening the directory\n");
        return -1;
    }

    entry = readdir(dirPointer); //Open the first directory entry
    while (entry != NULL){ //list the entries until the last one has been listed
        if(entry->d_type == DT_REG){ //List only regular files
            //open the file and handle errors
            fd = open(entry->d_name, O_RDONLY);
            if (fd < 0){
                printf("Error opening file\n");
                return -1;
            }
            //The size of the file equals the byte offset of seeking to the end of the file
            mySize = lseek(fd, 0, SEEK_END); //seek to the end of the file and save the number of bytes seeked over
            if(mySize < 0){
                printf("Error seeking for EOF");
                return -1;
            }

            printf("%s\t%d\n", entry->d_name, mySize); //print name and size of the entry

            //Close the file and check if it closes correctly
            if(close(fd) != 0){
                printf("Failed to close file descriptor\n");
                return -1;
            }
        }
        entry = readdir(dirPointer);    //get next entry
    }
    //Close the pointer to the directory and check if it closes correctly
    if (closedir(dirPointer) < 0){
        printf("Error closing the directory");
        return -1;
    }
	return 0;
}
