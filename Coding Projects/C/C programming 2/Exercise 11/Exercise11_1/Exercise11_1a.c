 #include <stdio.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/stat.h>

 #define IN_FILE "BtoA.txt"
 #define OUT_FILE "AtoB.txt"
 #define MESSAGE "Hello B"
 #define MAX_MESSAGE_SIZE 16

int main(void){
   
   int outFile_fd;
   if((outFile_fd = open(OUT_FILE, O_CREAT | O_WRONLY | O_NONBLOCK, 0666)) == -1){

      printf("ERROR opening file: %s\n", OUT_FILE);
      return 1;
   }

   int inFile_fd;
   if ((inFile_fd = open(IN_FILE, O_CREAT | O_RDONLY | O_NONBLOCK, 0444)) == -1){

      printf("ERROR opening file: %s\n", IN_FILE);
      return 2;
   }

   ssize_t bytesWritten = write(outFile_fd, MESSAGE, strlen(MESSAGE));

   if (bytesWritten == -1){
            
      printf("ERROR writing to file: %s\n", OUT_FILE);
      return 3;
   }
   
   char receivedMessage[MAX_MESSAGE_SIZE];

   while (1){

      ssize_t bytesRead = read(inFile_fd, receivedMessage, MAX_MESSAGE_SIZE);
      if (bytesRead > 0){

         receivedMessage[bytesRead] = '\0';
         printf("%s\n", receivedMessage);

         sleep(1);

         bytesWritten = write(outFile_fd, MESSAGE, strlen(MESSAGE));
         if (bytesWritten == -1){
            
            printf("ERROR writing to file: %s\n", OUT_FILE);
            return 3;
         }
      }
   }

   close(inFile_fd);
   close(outFile_fd);

   return 0; 
}