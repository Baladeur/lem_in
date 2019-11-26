/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 11:22:42 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:24 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

static int	is_type(const char *format, int i)
{
	if (format[i] == 'c' || format[i] == 'p' || format[i] == 's' ||
		format[i] == 'd' || format[i] == 'i' || format[i] == 'o' ||
		format[i] == 'u' || format[i] == 'x' || format[i] == 'X' ||
		format[i] == 'f')
		return (0);
	else
		return (1);
}

static char	*take_instructions(const char *format, int i)
{
	int		tmp;
	char	*str;
	int		k;
	int		j;

	i++;
	tmp = i;
	if (!format)
		return (NULL);
	while (is_type(format, i) && format[i] != '%' && format[i])
		i++;
	if (!(str = malloc(sizeof(*format) * ((i - tmp + 1) + 1))))
		return (NULL);
	k = tmp;
	j = 0;
	while (format[k] && k < tmp + (i - tmp + 1))
		str[j++] = format[k++];
	str[j] = '\0';
	return (str);
}

static int	display_helper(va_list ap, char *inst, int i, t_data *data)
{
	int	len;

	len = ft_strlen(inst);
	i = i + len;
	struct_malloc(data);
	cleaner(data);
	parser(inst, data);
	finalizer(data);
	dispatcher(ap, data);
	return (i);
}

static int	put_text(va_list ap, const char *format, char *instruc, int index)
{
	int		i;
	t_data	data;
	int		ret;

	i = 0;
	ret = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar(format[i]);
			index++;
		}
		if (format[i] == '%')
		{
			instruc = take_instructions(format, i);
			i = display_helper(ap, instruc, i, &data);
			ret += data.tool->ret;
			free_malloc(&data);
		}
		i++;
	}
	if (instruc)
		free(instruc);
	return (index + ret);
}

int			ft_printf(const char *format, ...)
{
	va_list ap;
	int		nb;
	int		index;
	char	*instruc;

	instruc = NULL;
	index = 0;
	va_start(ap, format);
	nb = put_text(ap, format, instruc, index);
	va_end(ap);
	return (nb);
}
