#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_COMMAND_LINE_LEN 1024
#define PORT 8080

char* getCommandLine(char *command_line){
    do { 
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
    } while (command_line[0] == 0x0A);  // Ignore just ENTER
    command_line[strlen(command_line) - 1] = '\0';  // Remove newline
    return command_line;
}

int main(int argc, char const* argv[]) 
{ 
    int sockID = socket(AF_INET, SOCK_STREAM, 0); 
    char *token, *cp;
    char buf[MAX_COMMAND_LINE_LEN];
    char responseData[MAX_COMMAND_LINE_LEN];

    struct sockaddr_in servAddr; 
  
    servAddr.sin_family = AF_INET; 
    servAddr.sin_port = htons(PORT); 
    servAddr.sin_addr.s_addr = INADDR_ANY; 
  
    int connectStatus = connect(sockID, (struct sockaddr*)&servAddr, sizeof(servAddr)); 
    if (connectStatus == -1) { 
        printf("Error connecting to server...\n"); 
        return -1;
    } 
    else { 
        while (1) {
            printf("Enter Command (or menu): ");
            getCommandLine(buf);

            send(sockID, buf, strlen(buf), 0);  // Send command to server
            cp = buf;
            token = strtok(cp, " ");

            if (strcmp(token, "exit") == 0) {
                exit(1);  // Exit client
            }
            else if (strcmp(token, "menu") == 0) {
                printf("COMMANDS:\n---------\n1. print\n2. get_length\n3. add_back <value>\n4. add_front <value>\n5. add_position <index> <value>\n6. remove_back\n7. remove_front\n8. remove_position <index>\n9. get <index>\n10. exit\n");
            }

            // Receive server response
            recv(sockID, responseData, sizeof(responseData), 0);  
            printf("\nSERVER RESPONSE: %s\n", responseData); 
            memset(buf, '\0', MAX_COMMAND_LINE_LEN);  // Clear buffer
        }
    } 
 
    return 0; 
}