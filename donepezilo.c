/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   donepezilo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:59:40 by mclaver-          #+#    #+#             */
/*   Updated: 2024/10/16 17:52:45 by dmarijan         ###   ########.fr       */
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
	ft_printf("msh: %s", err);
	reset_msh(mini);
	exit(-1);
}
