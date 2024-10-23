#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "list.h" // Include your linked list header file

#define PORT 8080
#define ACK "ACK: "

int main(int argc, char const* argv[]) 
{ 
    int n, val, idx;
    int servSockD = socket(AF_INET, SOCK_STREAM, 0); 
    if (servSockD < 0) {
        perror("Error creating socket");
        exit(1);
    }
    printf("Socket created successfully\n");

    char buf[1024];
    char sbuf[1024];
    char* token;

    struct sockaddr_in servAddr; 
    list_t *mylist;

    servAddr.sin_family = AF_INET; 
    servAddr.sin_port = htons(PORT); 
    servAddr.sin_addr.s_addr = INADDR_ANY; 

    if (bind(servSockD, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Error binding");
        exit(1);
    }
    printf("Socket bound successfully\n");

    if (listen(servSockD, 1) < 0) {
        perror("Error in listen");
        exit(1);
    }
    printf("Listening for connections...\n");

    int clientSocket = accept(servSockD, NULL, NULL); 
    if (clientSocket < 0) {
        perror("Error accepting connection");
        exit(1);
    }
    printf("Client connected!\n");

    mylist = list_alloc();  // Create the list

    while (1) {
        n = recv(clientSocket, buf, sizeof(buf), 0);
        buf[n] = '\0';

        if (n > 0) {
            token = strtok(buf, " ");
    
            if (strcmp(token, "exit") == 0) {
                list_free(mylist);  // Free the linked list
                exit(1);  // Exit server
            }
            else if (strcmp(token, "get_length") == 0) {
                val = list_length(mylist);  // Get the length
                sprintf(sbuf, "Length = %d", val);
            }
            else if (strcmp(token, "add_back") == 0) {
                token = strtok(NULL, " ");  // Get value
                val = atoi(token);  
                list_add_to_back(mylist, val);  // Add to back
                sprintf(sbuf, "%s%d", ACK, val);
            }
            else if (strcmp(token, "add_front") == 0) {
                token = strtok(NULL, " ");
                val = atoi(token);  
                list_add_to_front(mylist, val);  // Add to front
                sprintf(sbuf, "%s%d", ACK, val);
            }
            else if (strcmp(token, "add_position") == 0) {
                token = strtok(NULL, " ");
                idx = atoi(token);  // Get index
                token = strtok(NULL, " ");
                val = atoi(token);  // Get value
                list_add_at_index(mylist, idx, val);  // Add at index
                sprintf(sbuf, "%s%d", ACK, val);
            }
            else if (strcmp(token, "remove_back") == 0) {
                val = list_remove_from_back(mylist);  // Remove from back
                sprintf(sbuf, "Removed from back: %d", val);
            }
            else if (strcmp(token, "remove_front") == 0) {
                val = list_remove_from_front(mylist);  // Remove from front
                sprintf(sbuf, "Removed from front: %d", val);
            }
            else if (strcmp(token, "remove_position") == 0) {
                token = strtok(NULL, " ");
                idx = atoi(token);  
                val = list_remove_at_index(mylist, idx);  // Remove at index
                sprintf(sbuf, "Removed at index %d: %d", idx, val);
            }
            else if (strcmp(token, "get") == 0) {
                token = strtok(NULL, " ");
                idx = atoi(token);  
                val = list_get_elem_at(mylist, idx);  // Get element at index
                sprintf(sbuf, "Element at index %d: %d", idx, val);
            }
            else if (strcmp(token, "print") == 0) {
                sprintf(sbuf, "%s", listToString(mylist));  // Print list
            }

            send(clientSocket, sbuf, sizeof(sbuf), 0);  // Send response
        }
        memset(buf, '\0', sizeof(buf));
    }
  
    return 0; 
}