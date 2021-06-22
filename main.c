#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


int redirect_in(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int main (int argc, char const *argv[])
{
	pid_t pid;
	int i = 5;
	pid = fork();

	if(pid > 0)
	{
		printf("%d\n", ++i);
		printf("parent pid : %d\n", getpid());
		printf("pid from fork() to the parent %d\n", pid);
		redirect_in(argv[1]);	//[i]
		execve("/bin/cat", STDIN_FILENO, 0);
	}
	else if(pid == 0)
	{
		printf("%d\n", i);
		printf("child PID : %d\n" ,getpid());
		printf("pid from fork() ro the child: %d\n", pid);
	}
	return (0);
}

