#include <unistd.h>
#include <readline/readline.h>
#include "./libft/libft.h"
#define READ 0
#define WRITE 1

int main()
{
	pid_t pid1;
	int status1;

	pid1 = fork();

	if (pid1 < 0)
		printf(" no child");
	else if(pid1 == 0)
	{
		//명령받아오기 exit니면 실행하러	
		char *prompt;
		char *exe = readline(prompt);	
		char **exe_split = ft_split(exe , ' ');
		while(1)
		{
			pid_t pid2;
			int fildes[2];
			pipe(fildes);
		
			pid2 = fork();
			if (pid2 == 0) //자식
			{
				char *exe;
				exe = 0;
				read(fildes[READ], exe, ft_strlen(exe));
				execve("/bin/ls", exe, 0);
			}
			else if(pid2 > 0) //부모
			{
				int status2;
//***********	
				int i = 0;
				if(ft_strnstr("ls", exe_split[i], ft_strlen(exe)) == 0)
				{
					write(fildes[WRITE], exe_split[i], ft_strlen(exe));
					waitpid(pid2, &status2, 0);
				}
//***********
				else if(ft_strnstr("exit", exe, ft_strlen(exe)) == 0)
				{
					exit(0);
				}
			//exit이면 종료
			}
		}
	}
	else if(pid1 > 0) //할아버지
	{
		printf("welcome new shell");
		waitpid(pid1, &status1, 0);
	}
}
