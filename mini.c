#include <unistd.h>
#include <readline/readline.h>
#include "./libft/libft.h"
#include <stdio.h>
#define READ 0
#define WRITE 1

/* stdin  0
## stdout 1
*/
void ft_print_wheel()
{
	printf("---------------------------------\n");
	printf("|                               |\n");
	printf("|                               |\n");
	printf("|                               |\n");
	printf("|                               |\n");
	printf("|                               |\n");
	printf("|                               |\n");
	printf("|                               |\n");
	printf("|         /-\\        /-\\        |\n");
	printf("----------| |--------| |---------\n");
	printf("          \\-/        \\-/        \n");
}
int main()
{
	pid_t pid1;
	pid1 = fork();
	int status1;

	if (pid1 < 0)
		printf(" no child");
	else if(pid1 == 0)
	{
		char *input;
		char *output;
		while(1)
		{
			pid_t  pid2;
			int fildes[2];
			int status2;
		output = readline(input);
		char **output_split =ft_split(output, ' ');
			int i = 0;	
			while(i < 3)
			{
				if (ft_strnstr("exit", output_split[i], ft_strlen(output_split[i])) == 0)
					exit(0);
				++i;
			}
					pid2 = fork();
			if(pid2 == 0)
			{
				dup2(fildes[READ], 1);
				execve("bin/ls", output_split, 0 );
			}
			else if(pid2 > 0)
			{
				int status2;

				int i = 0;
				if(ft_strnstr("ls", output_split[i], ft_strlen(output_split[i])) == 0)
				{
					dup2(0, fildes[WRITE]);
					waitpid(pid2, &status2, 0);
				}
			}	
				//output이라는 명령어를 사용할 수 있도록 만들기!
		printf("i m father\n");
		}
	}
	else if(pid1 > 0) //할아버지
	{
		ft_print_wheel();
		printf("i m grandfather IN\n");
		waitpid(pid1, &status1, 0);
		printf("good bye see u\n");
	}
}
