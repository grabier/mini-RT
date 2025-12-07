/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:25:17 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/25 18:51:29 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_sphere_point(char **sp_aux, double f)
{
	if (ft_count_list(sp_aux) != 3)
		return (printf("Error\nsphere point parsing\n"), ft_free(sp_aux), 0);
	if (!ft_check_point(f, ft_atod(sp_aux[1]), ft_atod(sp_aux[2])))
		return (printf("sp point invalid\n"), ft_free(sp_aux), 0);
	return (1);
}

int	ft_parse_sphere(char **sp, t_parse *p)
{
	t_vec	point;
	t_color	c;
	char	**sp_aux;
	double	f;

	if (ft_count_list(sp) != 4)
		return (printf("sp invalid\n"), ft_free(sp), 0);
	sp_aux = ft_split(sp[1], ',');
	f = ft_atod(sp_aux[0]);
	if (!ft_parse_sphere_point(sp_aux, f))
		return (ft_free(sp), 0);
	point = ft_init_vec(f, ft_atod(sp_aux[1]), ft_atod(sp_aux[2]));
	ft_free(sp_aux);
	f = ft_atod(sp[2]);
	if (f <= 0 || fabs(f - 2.232323) < 0.0001)
		return (printf("sp diam invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	sp_aux = ft_split(sp[3], ',');
	if (!ft_check_color(sp_aux))
		return (printf("sp color invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	c = ft_init_color(sp_aux);
	ft_sphadd_back(&p->sp, ft_sphnew(point, f, c));
	return (p->sp_count++, ft_free(sp_aux), ft_free(sp), 1);
}

int	ft_check_color(char **sp)
{
	int	a;
	int	b;
	int	c;

	if (ft_count_list(sp) != 3)
		return (0);
	a = ft_atoi(sp[0]);
	b = ft_atoi(sp[1]);
	c = ft_atoi(sp[2]);
	if (a == -1 || b == -1 || c == -1)
		return (0);
	if (a > 255 || b > 255 || c > 255 || a < 0 || b < 0 || c < 0)
		return (0);
	return (1);
}

int	ft_check_point(double x, double y, double z)
{
	if (fabs(x - 2.232323) < 0.0001 || fabs(y - 2.232323) < 0.0001 || fabs(z
			- 2.232323) < 0.0001)
		return (0);
	return (1);
}

int	ft_init_t_color_sp(t_parse *p, int r, int g, int b)
{
	t_sph	*head;

	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (0);
	head = p->sp;
	while (p->sp->next)
		p->sp = p->sp->next;
	p->sp->color.r = (unsigned char)r;
	p->sp->color.g = (unsigned char)g;
	p->sp->color.b = (unsigned char)b;
	p->sp = head;
	return (1);
}
