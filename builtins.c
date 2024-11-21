/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:50:29 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/21 15:33:41 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

//el wait en linea 21 sirve para prevenir que escribamos mnsj de error
//al mismo tiempo que un hijo en pipe, y no hace nada si no hay hijos :D
int	ft_builtdads(t_msh *mini, char **arr)
{
	int	argc;

	if (mini->hasbuiltins)
		wait(NULL);
	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "export\0", 7))
	{
		if (argc > 1)
			argc = ft_export_create(mini, arr, 1);
		else
			argc = ft_export_print(mini, mini->env);
		array_free(arr);
		mini->returnval = argc;
		return (1);
	}
	else if (!ft_strncmp(arr[0], "exit\0", 5))
	{		
		mini->returnval = ft_exit(mini, arr);
		array_free(arr);
		return (1);	
	}	
	else if (!ft_strncmp(arr[0], "unset\0", 6))
	{
		if (mini->pipelen == 0)
			ft_unset(mini, arr);
		array_free(arr);
		mini->returnval = 0;
		return (1);
	}
	else if (!ft_strncmp(arr[0], "pwd\0", 4))
	{
		ft_pwd(mini);
		array_free(arr);
		mini->returnval = 0;
		return (1);
	}
	else if (!ft_strncmp(arr[0], "cd\0", 3))
	{
		mini->returnval = ft_cd(mini, arr, argc);
		array_free(arr);
		return (1);
	}
	return (0);
}
//estos son los builtins que mira el hijo
void	ft_builtins(t_msh *mini, char **arr)
{
	int	argc;

	argc = ft_argc(arr);
	if (!ft_strncmp(arr[0], "env\0", 4))
	{
		array_free(arr);
		if (argc > 1)
			childexit(1, mini, "env: No options or arguments allowed!\n");
		ft_env(mini, mini->env);
	}
	else if (!ft_strncmp(arr[0], "export\0", 7))
	{
		if (argc > 1)
			argc = ft_export_create(mini, arr, 1);
		else
			argc = ft_export_print(mini, mini->env);
		array_free(arr);
		childexit(argc, mini, "");
	}
	else if (!ft_strncmp(arr[0], "exit\0", 5))
	{
		array_free(arr);	
		childexit(0, mini, "");
	}	
	else if (!ft_strncmp(arr[0], "pwd\0", 4))
	{
		ft_pwd(mini);
		array_free(arr);
		childexit(0, mini, "");
	}
	else if (!ft_strncmp(arr[0], "echo\0", 5))
	{
		ft_echo(arr);
		array_free(arr);
		childexit(0, mini, "");
	}
	else if (!ft_strncmp(arr[0], "cd\0", 3))
	{	
		ft_cd(mini, arr, argc);
		array_free(arr);
		childexit(1, mini, "");
	}
	else if (!ft_strncmp(arr[0], "unset\0", 6))
	{
		ft_unset(mini, arr);
		array_free(arr);
		childexit(0, mini, "");
	}
}

int	ft_exit(t_msh *mini, char **arr)
{
	int				argc;
	unsigned char	buf;

	argc = ft_argc(arr);
	if (argc > 2)
	{
		ft_printf(2, "msh: exit: too many arguments\n");
		return (1);
	}
	if (ft_nodesize(mini->list) != 1)
		return ((unsigned char)ft_atoi(arr[1]));
	ft_printf(2, "exit\n");
	if (argc > 1)
	{
		buf = ft_atoi(arr[1]);
		array_free(arr);
		exit(buf);
	}
	array_free(arr);
	reset_msh(mini);
	array_free(mini->env);
	if (mini->envvar)
		stack_free_envvars(mini);
	exit(0);
}

void	ft_env(t_msh *mini, char **envp)
{
	int			i;
	t_envvar	*tmp;

	i = 0;
	while (envp[i])
	{
		ft_printf(1, "%s\n", envp[i]);
		i++;
	}
	tmp = mini->envvar;
	while (tmp)
	{
		if (tmp->hasvalue)
			ft_printf(1, "%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	childexit(0, mini, "");
}

int	ft_export_create(t_msh *mini, char **args, int i)
{
	char 	*tmp;
	char	*tmptwo;
	int		start;
	int		finnish;
	int		ret;

	ret = 0;
	while (args[i])
	{
		start = 0;
		finnish = 0;
		while (args[i][finnish] && args[i][finnish] != '=')
			finnish++;
		tmp = ft_substr(args[i], start, finnish);
		if (!isvalid(tmp))
		{
			ft_printf(2, "msh: export: %s: illegal var name\n", tmp);
			free(tmp);
			ret = 1;
		}
		else if (!args[i][finnish] && !my_findvar(tmp, mini->env, mini->envvar))
		{
			if (!ft_strncmp(tmp,"PWD\0", 4))
				append_envvar(&mini->envvar, tmp, mini->pwd, mini);
			else if (!ft_strncmp(tmp, "OLDPWD\0", 7))
				append_envvar(&mini->envvar, tmp, mini->oldpwd, mini);
			else
				append_envvar(&mini->envvar, tmp, NULL, mini);
		}
		else if (args[i][finnish] == '=')
		{
			if (my_findvar(tmp, mini->env, mini->envvar))
			{
				tmptwo = ft_strjoin("unset ", tmp);
				do_last(mini, tmptwo);
				free(tmptwo);
			}
			append_envvar(&mini->envvar, tmp, \
				ft_substr(args[i], finnish + 1, ft_strlen(args[i])), mini);
		}
		else
			free(tmp);
		i++;
	}
	return (ret);
}

int	ft_export_print(t_msh *mini, char **envp)
{
	int			i;
	t_envvar	*tmp;
	int			j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		ft_printf(1, "declare -x ");
		while (envp[i][j] && envp[i][j] != '=')
			ft_printf(1, "%c", envp[i][j++]);
		ft_printf(1, "=\"");
		while (envp[i][j++])
			ft_printf(1, "%c", envp[i][j]);
		ft_printf(1, "\"\n");
		i++;
	}
	tmp = mini->envvar;
	while (tmp)
	{
		ft_printf(1, "declare -x %s", tmp->name);
		if (tmp->hasvalue)
			ft_printf(1, "=\"%s\"", tmp->value);
		ft_printf(1, "\n");
		tmp = tmp->next;	
	}
	return (0);
}

void	ft_pwd(t_msh *mini)
{
	ft_printf(1, "%s\n", mini->pwd);
}

void	ft_echo(char **arr)
{
	int	j;
	int	i;

	i = 1;
	j = 0;
	if (arr[i] && !ft_strncmp(arr[i], "-n", 2))
		i++;
	while (arr[i])
	{
		while (j < (int)ft_strlen(arr[i]) && arr[i][j])
		{
			ft_printf(1, "%c", arr[i][j]);
			j++;
		}
		if (arr[i + 1])
			ft_printf(1, " ");
		j = 0;
		i++;
	}
	if (!arr[1] || ft_strncmp(arr[1], "-n", 2))
		ft_printf(1, "\n");
}
