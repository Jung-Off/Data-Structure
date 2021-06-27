#include "main.h"

void init_exe(t_exe *exe, char *argv)
{
	char **cmd;
	
	cmd = ft_split(cmd, ' ');
	
	exe->path[0] = ft_strjoin("/usr/local/bin/", cmd[0]);
	exe->path[1] = ft_strjoin("/usr/bin/", cmd[0]);
	exe->path[2] = ft_strjoin("/bin/", cmd[0]);
	exe->path[3] = ft_strjoin("/usr/sbin/", cmd[0]);
	exe->path[4] = ft_strjoin("/sbin/", cmd[0]);

	exe->argv = cmd;
	exe->envp = NULL;
}

//////////////////////////////////////parent

int connect_file_to_stdin(const char *infile)
{
	int fd;

	fd = open(infile, O_RDWR);
	if(fd < 0)
	{
		perror(infile);
		return (ERROR);
	}
	dup2(fd ,STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

void connect_stdout_pipe_w(int pipefd[2])
{
	dup2(STDOUT_FILENO, pipefd[WRITE]);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
}

void use_pipe_w_to_stdout(char *argv)
{
	t_exe exe;
	int i;

	i = 0;
	init_exe(&exe, argv);
	while(i < 5)
		execve(exe.path[i], exe.argv, exe.envp);
	perror(argv);
}
////////////////////////////////////////child

int connect_file_to_stdout(char *outfile)
{
	int fd;

	fd = open(outfile, O_RDWR | O_CREAT, 0644);
	if( fd < 0)
	{
		perror(outfile);
		return(ERROR);
	}
	dup2(fd ,STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

void connect_stdin_pipe_r(int pipefd[2])
{
	dup2(pipefd[1], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

void use_pipe_r_to_file(char *argv)
{
	t_exe exe;
	int i;

	i = 0;
	init_exe(&exe, argv);
	while(i < 5)
		execve(exe.path[i], exe.argv, exe.envp);
	perror(argv);
}

int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t pid;


	pipe(pipefd);
	pid = fork();
	if(pid > 0)
	{
		connect_file_to_stdin(argv[1]);
		connect_stdout_pipe_w(pipefd);
		use_pipe_w_to_stdout(argv[2]);
	}
	else if(pid == 0)
	{
		connect_file_to_stdout(argv[4]);			
		connect_stdin_pipe_r(pipefd);
		use_pipe_r_to_file(argv[3]);	
	}
	return(0);
}
