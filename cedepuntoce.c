/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cedepuntoce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:58:41 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/06 18:24:26 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//rutas absolutas Y relativas... creo que chdir ya controla bastante

void	add_path_to_env(t_msh *mini)
{
	int	i;
	char	*tmp;

	getenv
}

void	change_path(t_msh *mini)
{
//	mini-> OLDPWD tambien, el env no es necesariamente modificable no?
	free(mini->pwd);
	mini->pwd = getcwd(NULL, sizeof(NULL));
}

void	ft_cd(t_msh *mini, char **arr, int argc)
{
	int	errnum;
//afegir variable pwd en mini
//	if (!(argc > 1))
//		if (chdir(getenv("HOME")))
 			
//	change path a "HOME=" con getenv es ez, lo unico q si nos lo borran/cambian se lia
//	else if (!ft_strncmp(arr[1], "-\0", 2))//(?? no conocia lo de cd -)
//	change path a "OLDPWD=" same q con home
//	else
//	{
	errnum = chdir(arr[1]);
	if (errnum)
		errexit(mini, "cagaste we (cd error)");
			//error papito
//	}
	//vigilar el errnum de los 2 primeros ifs
	change_path(mini);
	add_path_to_env(mini);
//return o lo q sea (TIENE QUE HACERLO EL PAPA)
}
