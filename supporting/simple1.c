#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - shell proggram
 * Programmer: Isaac-ik
 * Description: Simple shell program
 * @argc: number of arguments
 * @argv: argument vector
 * Return: an integer
 */
int main(int argc, char **argv) {
    char *cmdBuff;
    size_t n = 10;
    int v;
    pid_t pid;
    ssize_t e;

    cmdBuff = (char *)malloc((sizeof(char)) * n);
    if (cmdBuff == NULL) {
        return (-1);
    }
    printf("$ ");

    e = getline(&cmdBuff, &n, stdin);
    if (e == -1) {
        printf("Error in getline\n ");
        free(cmdBuff);
        return (-1);
    }

    /* Tokenizing the command line input into arguments */
    char *token;
    const char delimiters[] = " \n"; /* Include newline as delimiter */
    token = strtok(cmdBuff, delimiters);
    int argCount = 0;
    char **args = malloc(sizeof(char *) * (n / 2)); /* Allocate space for arguments */

    while (token != NULL) {
        args[argCount] = token;
        argCount++;
        token = strtok(NULL, delimiters);
    }
    args[argCount] = NULL; /* The last argument should be NULL for execve */

    pid = fork();
    if (pid == 0) {
        /* Child process */
        v = execvp(args[0], args); /* Use execvp to search for the command in PATH */
        if (v == -1) {
            printf("Error in execvp\n");
            free(cmdBuff);
            free(args);
            return (-1);
        }
    } else if (pid > 0) {
        /* Parent process */
        wait(NULL);
    } else {
        /* Error in fork */
        printf("Error in fork\n");
        perror("ERROR");
        free(cmdBuff);
        free(args);
        return (-2);
    }

    printf("No Error\n");
    free(cmdBuff);
    free(args);

    return (0);
}

