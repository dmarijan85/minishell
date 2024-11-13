//metele un header a este hijo de putA

#include "minishell.h"

void msh_init(t_msh *mini) //este es el del loop, igual tendria sentido cambiarle el nombre tipo msh clean, ns
{
	mini->list = NULL;
	mini->reset = false;
	mini->herectr = 0;
	mini->args = NULL;
	mini->pipelen = 0;
}

static char	**whileloop_cpy_env(char **env, char **ret, char **og)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (og[size])
		size++;
	while (i < size)
	{
		ret[i] = ft_strdup(env[i]);
		if (!ret[i])
		{
			array_free(ret);
			return (NULL);
    	}
    	i++;
	}
	ret[i] = NULL;
	return (ret);
}

char	**cpy_env(char **env)
{
	char	**ret;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	ret = ft_calloc(sizeof(char *), i + 1);
	if (!ret)
		return (NULL);
	ret = whileloop_cpy_env(env, ret, env);
	return (ret);
}

void  msh_start(t_msh *mini, char **env) 
{
	char *tmp;

	mini->env = cpy_env(env);
	if (!mini->env)
		errexit(mini, "environment copy failure?!\n");
	mini->pwd = getenv("PWD");
	mini->envvar = NULL;
	if (!mini->pwd)
		errexit(mini, "Va no em toquis els qllons germanet\n");
	mini->pwd = getcwd(NULL, 0);
	if (!getenv("PWD"))
	{
		tmp = ft_strjoin("export PWD=", mini->pwd);
		do_last(mini, tmp, mini->env);
		wait(NULL);
		free(tmp);
	}
	mini->oldpwd = NULL;
	if (!getenv("OLDPWD"))
	{
		do_last(mini, "export OLDPWD", mini->env);
		wait(NULL);
	}
	mini->oldpwd = ft_strdup(my_getenv("OLDPWD", mini->env, mini->envvar));
}
