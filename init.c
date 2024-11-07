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

static char	**whileloop_cpy_env(char **env, char **ret) //static pq sirve solo para esto no?
{
	int	i;

	i = 0;
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		if (!ret[i])
		{
			array_free(ret);
			return (NULL);
    }
    i++;
	}
	env[i] = NULL;
	return (ret);
}

char	**cpy_env(char **env)
{
	char	**ret;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	ret = malloc(sizeof(char *) * i);
	if (!ret)
		return (NULL);
	ret = whileloop_cpy_env(env, ret);
	return (ret);
}

void  msh_start(t_msh *mini, char **env) //deberia ir en el main en vez de las lineas q tenemos iniciando env pwd etc
{
  mini->env = cpy_env(env);//quiero el env nuestro, no el original / ALSO que pasa si falla el malloc?
	mini->envismallocd = true; //no se si al hacer el cpy_env hace falta este flag?
	mini->pwd = getenv("PWD");
	if (!mini.pwd)  //diria que esto no deberia ir así, pero ya lo arreglaremos pq ns como hay que hacerlo
		errexit(&mini, "Va no em toquis els qllons germanet\n")
}
