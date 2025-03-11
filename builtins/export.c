void	builtin_export(array, t_env *env)
{
	//usage: export VAR_NAME="Hello" or export VAR_1="first" VAR_2="second" WORKS WITHOUT QUOTES and
	//with single quotes
	//in case of VAR_NAME= adds VAR_NAME= to env list
	//!!if no arguments given, just prints exported variables in alphabetical order with "declare -x" in front

	//when adding a variable to the environment array, first check if the array is full
	//e.g. env->len + 1 >= env->capacity

	t_env	*alphalist;

	if (!array[1])
	{
		alphalist = sort_env(env);
		//alphabetise env list ft_strcmp? make new linked list in which nodes are in order?
		while (alphlist != NULL)
		{
			printf("declare -x");
			print alphlist->value[i]
			alphlist = alphlist->next;
			i++;
		}
		return ; //return success
	}
	//check if array[1] is valid input
	//check if env var already exists, in which case replace
	//create new node for env

	//something like env->envp[env->len] = tmp;
}
