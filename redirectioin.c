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

int redirect_out(const char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if(fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int main(int argc, char const *argv[])
{
	int i;
	
	i = 1;
//	while(i < argc - 2) //배열이랑 맨뒤에 것 빼기
//	{
		redirect_in(argv[1]);	//[i]
		execve("/bin/cat", STDIN_FILENO, 0);
		redirect_out(argv[2]);	//[i]
//	}
	return (0);
}
