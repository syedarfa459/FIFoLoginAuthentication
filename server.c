#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
int validator(char user[256],char pswd[256]);
int main() 
{ 
    int fd,fd1,fd2,fd3,fd4; 
    pid_t pid;
    // FIFO file path 
    char * myfifo = "/tmp/myfifo";
   
    char * myfifousername = "/tmp/myfifousername";
    char * myfifopassword = "/tmp/myfifopassword"; 
    char * myfiforesult = "/tmp/myfiforesult";
    
  
    // Creating the named file(FIFO) 
    mkfifo(myfifo, 0666); 
    
    mkfifo(myfifousername, 0666);
    mkfifo(myfifopassword, 0666);
  
    
    char username[20],password[20];
    
    if((pid=fork())==-1){
    	perror("Child Error");
    }
   
    while (1) 
    { 
    	
    	char mymenu[200]="\nWelcome Client! This is your user Authentication System\n";      
  
        while(1){


            	if(pid==0){
                fd = open(myfifo,O_WRONLY); 

		write(fd,mymenu,strlen(mymenu)+1);
		
		close(fd); 
		
		fd2 = open(myfifousername,O_RDONLY); 
		read(fd2, username, 10);
		
		close(fd2);
		
	       
		fd3 = open(myfifopassword,O_RDONLY); 
		read(fd3, password, 10);
		
		close(fd3);

     
                    
                    validator(username,password);
                    
                }

            }
                  
        
    }
    
    return 0; 
} 

int validator(char user[256],char pswd[256]){
char * fifoMsg = "/tmp/fifoMsg";
mkfifo(fifoMsg,0666);
    char line[256];
    int flag=0;

    int fdMsg=open(fifoMsg, O_RDWR);

    FILE* file = fopen("users.txt", "r"); 

        for(int i=1;i>=0;i--){
                fgets(line, sizeof(line), file);
                
                if(i==1){
                    if(strcmp(user,line)==0){
                        flag++;
                    }
                }
                if(i==0){
                    if(strcmp(pswd,line)==0){
                        flag++;
                    }
                }
        }
        if(flag==2){
             
             if( write(fdMsg,"InValid User",sizeof("InValid User"))==-1){

                    return 2;
                }

        }else{
            
            if( write(fdMsg,"Valid user",sizeof("Valid User"))==-1){

                    return 2;
                }
        }
   fclose(file);
   close(fdMsg);

}
