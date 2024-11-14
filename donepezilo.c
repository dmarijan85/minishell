/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   donepezilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:59:40 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/14 12:23:02 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_msh(t_msh *mini)
{
	mini->pipelen = 0;
	el_fregading(mini);
	mini->list = NULL;
	mini->args = NULL;
}

void	errexit(t_msh *mini, char *err)
{
	if (err && *err)
		ft_printf(2, "msh: %s", err);
	if (mini->args && mini->herectr == 0)
		add_history(mini->args);
	reset_msh(mini);
	minishell_loop(mini);
}

void	childexit(t_msh *mini, char *err)
{
	if (err && *err)
		ft_printf(2, "msh: %s", err);
	reset_msh(mini);
	array_free(mini->env);
	if (mini->envvar)
		stack_free_envvars(mini);
	exit(-1);
}
