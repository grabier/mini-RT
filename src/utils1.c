/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:32:25 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/25 18:51:42 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

uint32_t	rgb_to_hex_alpha(t_color color)
{
	return ((color.r << 24) | (color.g << 16) | (color.b << 8) | 255);
}

int	ft_check_extension(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (i < 3)
		return (0);
	if (file[i - 1] != 't' || file[i - 2] != 'r' || file[i - 3] != '.')
		return (0);
	return (1);
}

int	ft_double_check(char *str)
{
	int	i;
	int	cont;

	i = 0;
	cont = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '.' && str[i] != '-')
			return (0);
		if ((str[i] == '.' && (!str[i + 1])) || (i == 0 && str[i] == '.'))
			return (0);
		if (str[i] == '.')
			cont++;
		i++;
	}
	if (cont > 1)
		return (0);
	return (1);
}

int	ft_count_list(char	**list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}
