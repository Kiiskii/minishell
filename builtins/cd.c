void	builtin_cd(char **array, t_env *env)
{
	if (array[1] != a valid path) //or 0 depending on contents of array
	{
		printf("Provide a valid path for command cd");
		error_and_exit;
	}
	chdir(arr[1]);
	//error check this
}



//int	builtin_cd(void)
//{
//	char	*pwd;

//	pwd = getcwd(NULL, 0);
//    printf("pwd before chdir: %s\n", pwd);
//	chdir("/home/lguillen/minishell_github/execution");
//	pwd = getcwd(NULL, 0);
//    printf("pwd after chdir: %s\n", pwd);
//	return (0);
//}

//int	main(void)
//{
//	builtin_cd();
//	return (0);
//}