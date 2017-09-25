#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mytoc.h"
#include "mystrlib.h"

#define BUFFERSIZE 150

int main(int argc, char** argv, char** envp)
{
	char** args, tokenVec, pathVec;
	char* string, program;
	int pid, i = 0;

	while(1)
	{
		string = (char*) malloc(BUFFERSIZE);

		write(1, "$ ", 2);
		read(0, string, BUFFERSIZE);

		if(strComp(string, "exit\n"))
			exit(0);

		else
		{
			args = Mytoc(string, ' ');

			pid = fork();

			if(pid < 0)
			{
				fprintf(stderr, "Unsuccessful fork()\n");
				exit(1);
			}
			else if(pid == 0)
			{
				while(envp[i] != (char*)0)
				{
					tokenVec = Mytoc(envp[i], '=');

					if(strComp(tokenVec[0], "PATH"))
					{
						pathVec = Mytoc(tokenVec[1], ':');
					}

					for (int i = 0; tokenVec[i] != '\0'; i++)
					{
						free(tokenVec[i]);
					}
					free(tokenVec);

					i++;

				}
				execve("/bin/ls", args, envp);
				printf("Command not found\n")
				exit(0);
			}
		}

		free(string);
	}
}
