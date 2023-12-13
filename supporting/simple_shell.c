#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

char **splitCmd(char *cmdline, char *delim)
{
	char **argV;
	char *token;
	int i = 0;

	/* Tokenizing the cmd */
	token = strtok(cmdline, delim);
	while (token != NULL)
	{
		argV[i] = token;
		printf("the argument is %i is %s\n", i, argV[i]);
		token = strtok(NULL, delim);
		i++;
	}
	argV[i] = NULL;
	
	return (argV);
}

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
	char *cmdline, *token, *cmd;
	size_t n = 10;
	ssize_t st;
	char **argV, **envp = {NULL};
	int ch2, i = 0;
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

	/* create a child process */
	pid = fork();
	if (pid == -1)
	{
		printf("Error 3\n");
		return (-1);
	}
	argV = splitCmd(cmdline, delim);
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
