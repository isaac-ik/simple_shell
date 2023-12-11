#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int execueteCmd(char **args, char *cmdBuff);

/**
 * gettokens - part of the shell program
 * Programmer: Isaac-ik
 * Description: split the command text into tokens and stores in buffer space
 * @argV: array of buffer space
 * @cmdBuff: command text
 * Return: an integer
 */
int gettokens(char **argV, char *cmdBuff)
{
	/* Tokenizing the command line input into arguments */
	char *token;
	const char delimiters[] = " \n"; /* Include newline as delimiter */
	int argCount = 0;

	token = strtok(cmdBuff, delimiters);
	while (token != NULL)
	{
		argV[argCount] = token;
		argCount++;
		token = strtok(NULL, delimiters);
	}
	argV[argCount] = NULL; /* The last argument should be NULL for execve */

	return (1);
}
/**
 * main - shell proggram
 * Programmer: Isaac-ik
 * Description: Simple shell program
 * @argc: number of arguments
 * @argv: argument vector
 * Return: an integer
 */
int main(int argc, char **argv)
{
	char *cmdBuff;
	size_t n = 10;
	int status;
	ssize_t e;

	cmdBuff = (char *)malloc((sizeof(char)) * n);
	if (cmdBuff == NULL)
	{
		return (-1);
	}
	printf("$ ");

	e = getline(&cmdBuff, &n, stdin);
	if (e == -1)
	{
		printf("Error in getline\n ");
		free(cmdBuff);
		return (-1);
	}

	/* Allocate space for arguments */
	char **args = malloc(sizeof(char *) * (n / 2));

	gettokens(args, cmdBuff);

	status = execueteCmd(args, cmdBuff);
	if (status == -1)
		return (-1);

	printf("No Error\n");
	free(cmdBuff);
	free(args);
	return (0);
}

/**
 * execueteCmd - shell proggram
 * Programmer: Isaac-ik
 * Description: executes the command from the argumnet buffer
 * and free memory
 * @args: arguments buffer
 * @cmdBuff: command text
 * Return: an integer
 */
int execueteCmd(char **args, char *cmdBuff)
{
	int v;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		v = execvp(args[0], args); /* Use execvp to search for the command in PATH */
		if (v == -1)
		{
			printf("Error in execvp\n");
			free(cmdBuff);
			free(args);
			return (-1);
		}
	}
	else if (pid > 0)
	{
		/* Parent process */
		wait(NULL);
	}
	else
	{
		/* Error in fork */
		printf("Error in fork\n");
		perror("ERROR");
		free(cmdBuff);
		free(args);
		return (-1);
	}

	return (0);
}

