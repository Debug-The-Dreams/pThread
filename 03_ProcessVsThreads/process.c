#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
    int pid = fork();
    int var = 0;

    if(pid < 0) {
        perror("Fork failed");
        return 1;
    }
    if(pid == 0)
    {
        // Child process
        var += 1; 
        sleep(2);
    } 

    sleep(2);
    printf("Var = %d\n", var);

    if(pid != 0) {
        // Child process
            wait(NULL); // Wait for child process to finish
    } 
    return EXIT_SUCCESS;
}