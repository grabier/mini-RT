/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:58:16 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/25 18:50:29 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	ft_init_vec(double x, double y, double z)
{
	t_vec	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_color	ft_init_color(char **sp)
{
	int		a;
	int		b;
	int		c;
	t_color	color;

	a = ft_atoi(sp[0]);
	b = ft_atoi(sp[1]);
	c = ft_atoi(sp[2]);
	color.r = a;
	color.g = b;
	color.b = c;
	return (color);
}

t_parse	*ft_init_parse(void)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	parse->a = 0;
	parse->c = 0;
	parse->l = 0;
	parse->sp_count = 0;
	parse->pl_count = 0;
	parse->cy_count = 0;
	parse->sp = NULL;
	parse->pl = NULL;
	parse->cy = NULL;
	parse->cam = NULL;
	parse->hit = NULL;
	return (parse);
}

int	ft_hitsize(t_hit *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
