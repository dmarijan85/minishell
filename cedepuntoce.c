/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cedepuntoce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaver- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:58:41 by mclaver-          #+#    #+#             */
/*   Updated: 2024/11/05 17:42:31 by mclaver-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//rutas absolutas Y relativas... creo que chdir ya controla bastante

void	ft_cd(t_msh *mini, char **arr)
{
	int	errnum;
//afegir variable pwd en mini
	if (!(argc > 1))
//	change path a "HOME=" con getenv es ez, lo unico q si nos lo borran/cambian se lia
	else if (!ft_strncmp(arr[1], "-\0", 2))//(?? no conocia lo de cd -)
//	change path a "OLDPWD=" same q con home
	else
	{
		errnum = chdir(arr[1]);
		if (errnum)
			//error papito
	}
	//vigilar el errnum de los 2 primeros ifs
//change path(mini);
//add path to env
//return o lo q sea (TIENE QUE HACERLO EL PAPA)
}
