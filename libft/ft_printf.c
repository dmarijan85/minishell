/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:25:41 by dmarijan          #+#    #+#             */
/*   Updated: 2024/04/15 12:51:59 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "limits.h"

static int	printc(int c)
{
	return (write(1, &c, sizeof(char)));
}

static int	formatter(char const *input, int i, va_list args)
{
	unsigned int	u;

	u = 0;
	if (input[i] == 'c')
		return (printc(va_arg(args, int)));
	else if (input[i] == 's')
		return (pt_putstr(va_arg(args, char *)));
	else if (input[i] == 'd' || input[i] == 'i')
		return (pt_putnbr_fd(va_arg(args, int)));
	else if (input[i] == '%')
		return (printc('%'));
	else if (input[i] == 'u')
	{
		u = (unsigned int)va_arg(args, int);
		return (pt_putunsigned(u));
	}
	else if (input[i] == 'X' || input[i] == 'x')
		return (pt_puthex(input[i], va_arg(args, unsigned int)));
	else if (input[i] == 'p')
		return (pt_putptr(va_arg(args, void *)));
	return (-1);
}

int	printflogic(char const *input, int out, int ret, va_list args)
{
	int	temp;
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '%' && pt_strchr("cspdiuxX%", input[i + 1]))
		{
			i++;
			temp = formatter(input, i, args);
			if (temp == -1)
				return (-1);
			ret = ret + temp;
		}
		else
		{
			if (write(out, &input[i], sizeof(char)) == -1)
				return (-1);
			ret++;
		}
		i++;
	}
	return (ret);
}

int	ft_printstderr(char const *input, ...)
{
	va_list	args;

	va_start(args, input);
	return (printflogic(input, 2, 0, args));
}

int	ft_printf(char const *input, ...)
{
	va_list	args;

	va_start(args, input);
	return (printflogic(input, 1, 0, args));
}
/*
int	main()
{
	printf("hola me llamo \0danilo");
	puts("\n");
	ft_printf("hola me llamo \0danilo");
}
*/
