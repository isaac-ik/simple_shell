#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - entry point
 * Programmer: Isaac-ik
 * Description: a UNIX command program/interpreter
 * @argc: argumnet count
 * @argv: argument vector
 * Return: On sucess, 0. else -1
 */
int main(int argc, char **argv)
{
	char *cmdline;
	size_t n = 10;
	ssize_t st;
	char **argV, **envp = {NULL};
	int ch2, i = 1;
	pid_t pid;
	char *delim = " ";

	cmdline = (char *)malloc(sizeof(char) * n);

	/* Prompt */
	printf("$ ");

	st = getline(&cmdline, &n, stdin);
	if (st == -1)
	{
		printf("Error 1\n");
		return (-1);
	}
	/* Tokenizing the cmd */
	argV = (char **)malloc(sizeof(char *) * 5);
	argV[0] = strtok(cmdline, delim);
	while (cmdline != NULL)
	{
		argV[i] = strtok(NULL, delim);
		printf("the argument is %i is %s\n", i, argV[i]);
		i++;
	}
	argV[i] = '\0';

	/* create a child process */
	pid = fork();
	if (pid == -1)
	{
		printf("Error 3\n");
		return (-1);
	}
	if (pid == 0)
	{
		/* exceute the prompt */
		ch2 = execve(argV[0], argV, envp);
		if (ch2 == -1)
		{
			printf("Error 2\n");
			return (-1);
		}
	}
	if (pid > 0)
		wait(NULL);


	free(cmdline);
	return (0);
}
