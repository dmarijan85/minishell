/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cedepuntoce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:58:41 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/12 16:17:57 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//rutas absolutas Y relativas... creo que chdir ya controla bastante

void	add_path_to_env(t_msh *mini)
{
	int	i;
	char	*tmp;

	
}

void	change_path(t_msh *mini)
{
	free(mini->oldpwd);
	mini->oldpwd = mini->pwd;
//	free(mini->pwd); esta tia es tonta o soy retrasado?
	mini->pwd = getcwd(NULL, sizeof(NULL));
}

void	ft_cd(t_msh *mini, char **arr, int argc)
{
	int	errnum;
//afegir variable pwd en mini	
	if (chdir(arr[1])
		errexit(mini, "cagaste we (cd error)");
			//error papito
	change_path(mini);
	add_path_to_env(mini);
//return o lo q sea (TIENE QUE HACERLO EL PAPA)
}
