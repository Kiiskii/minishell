int	builtin_pwd(some array)
{
	char	*pathname;

	if (after pwd there is "-") //check the element in the array following pwd, it should be NULL 
	{
		printf("Options for pwd are not supported.");
		error_and_exit();
	}
	pathname = getcwd(NULL, 0);
	if (!pathname)
	{
		printf("Error getcwd");
		return (1);
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