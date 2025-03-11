#include "minishell.h"
#include <errno.h>

int	builtin_pwd(char **array)
{
	char	*pathname;

	if (array[1] && array[1][0] == "-")
	{
		printf("lash: pwd: options for pwd are not supported\n");
		return (2);
	}
	pathname = getcwd(NULL, 0);
	if (!pathname)
	{
		printf("Error: getcwd\n");
		return (1); //what error code? strerror(errno) ? or perror("getcwd") and return(errno)
	}
	printf("%s\n", pathname);
	free(pathname); //As an extension to the POSIX.1-2001 standard, glibc's getcwd()
       //allocates the buffer dynamically using malloc(3) if buf is NULL.
       //In this case, the allocated buffer has the length size unless size
       //is zero, when buf is allocated as big as necessary.  The caller
       //should free(3) the returned buffer.
	return (0);
}

//int	test_pwd(void)
//{
//	char	*name;
//
//	name = getcwd(NULL, 0);
//	printf("%s\n", name);
//	return (0);
//}
//
//int	main(void)
//{
//	test_pwd();
//	return (0);
//}
