#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main() 
{ 
    int fd,fd1,fd2,fd3,fd4; 
   
    char username[20],password[20];
    // FIFO file path 
    char * myfifo = "/tmp/myfifo";
    
    char * myfifousername = "/tmp/myfifousername";
    char * myfifopassword = "/tmp/myfifopassword"; 
   
    char * fifoMsg = "tmp/fifoMsg";
   
   
    char MESSAGEFROM[100];
    while (1) 
    { 
        
        // Open FIFO for Read only 
        fd1 = open(myfifo, O_RDONLY); 
  
        read(fd1, MESSAGEFROM, sizeof(MESSAGEFROM));  
        printf("%s\n", MESSAGEFROM); 
        close(fd1); 
        
        
        
        fd3 = open(myfifousername, O_WRONLY); 
        printf("\nEnter the username : ");
        scanf("%s",username);
        write(fd3, username, 20); 
        close(fd3);
        
        fd4 = open(myfifopassword, O_WRONLY); 
        printf("\nEnter the password : ");
        scanf("%s",password);
        write(fd4, password, 20); 
        close(fd4);
        
        //to read final result
        fd = open(fifoMsg, O_RDONLY); 
  	char receivemsg[100];
        // Read from FIFO 
        read(fd, receivemsg, 100); 
        // Print the read message 
        printf("%s\n", receivemsg);
        close(fd);  
  
    } 
    return 0; 
} 
