/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <dmarijan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:25:41 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/14 12:16:25 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "limits.h"

static int	printc(int out, int c)
{
	return (write(out, &c, sizeof(char)));
}

static int	formatter(int out, char const *input, int i, va_list args)
{
	unsigned int	u;

	u = 0;
	if (input[i] == 'c')
		return (printc(out, va_arg(args, int)));
	else if (input[i] == 's')
		return (pt_putstr(out, va_arg(args, char *)));
	else if (input[i] == 'd' || input[i] == 'i')
		return (pt_putnbr_fd(out, va_arg(args, int)));
	else if (input[i] == '%')
		return (printc(out, '%'));
	else if (input[i] == 'u')
	{
		u = (unsigned int)va_arg(args, int);
		return (pt_putunsigned(out, u));
	}
	else if (input[i] == 'X' || input[i] == 'x')
		return (pt_puthex(out, input[i], va_arg(args, unsigned int)));
	else if (input[i] == 'p')
		return (pt_putptr(out, va_arg(args, void *)));
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
			temp = formatter(out, input, i, args);
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

int	ft_printf(int out, char const *input, ...)
{
	va_list	args;

	va_start(args, input);
	return (printflogic(input, out, 0, args));
}
