
#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>


#define READ		0
#define WRITE		1
#define SUCCESS		0
#define ERROR		-1

//STDIN_FILENO	0
//STDOUT_FILENO	1

typedef struct s_exe
{
	char *path[5];
	char *const *argv;
	char *const *envp;
}				t_exe;


#endif


//파일을 열어 그리고 그걸 실행
