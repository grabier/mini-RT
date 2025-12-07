/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:33:03 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/25 18:51:10 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_plane_point(char **sp)
{
	if (ft_count_list(sp) != 3)
		return (printf("Error\nplane point parsing\n"), ft_free(sp), 0);
	if (!ft_check_point(ft_atod(sp[0]), ft_atod(sp[1]),
			ft_atod(sp[2])))
		return (printf("pl point invalid\n"), ft_free(sp), 0);
	return (1);
}

int	ft_parse_plane_vector(char **sp)
{
	if (ft_count_list(sp) != 3)
		return (printf("Error\nplane vector parsing\n"), ft_free(sp), 0);
	if (!ft_check_n_vector(ft_atod(sp[0]), ft_atod(sp[1]),
			ft_atod(sp[2])))
		return (printf("pl normal vector invalid\n"), ft_free(sp), 0);
	return (1);
}

int	ft_parse_plane(char **sp, t_parse *p)
{
	t_vec	p1;
	t_vec	p2;
	char	**sp_aux;

	sp_aux = ft_split(sp[1], ',');
	if (!ft_parse_plane_point(sp_aux))
		return (ft_free(sp), 0);
	p1 = ft_init_vec(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]),
			ft_atod(sp_aux[2]));
	ft_free(sp_aux);
	sp_aux = ft_split(sp[2], ',');
	if (!ft_parse_plane_vector(sp_aux))
		return (ft_free(sp), 0);
	p2 = ft_init_vec(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]),
			ft_atod(sp_aux[2]));
	ft_free(sp_aux);
	sp_aux = ft_split(sp[3], ',');
	if (!ft_check_color(sp_aux))
		return (printf("pl color invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	ft_pladd_back(&p->pl, ft_plnew(p1, p2, ft_init_color(sp_aux)));
	p->pl_count++;
	return (ft_free(sp_aux), ft_free(sp), 1);
}

int	ft_check_n_vector(double x, double y, double z)
{
	if (fabs(x - 2.232323) < 0.0001 || fabs(y - 2.232323) < 0.0001 || fabs(z
			- 2.232323) < 0.0001)
		return (0);
	if (x > 1 || x < -1 || y > 1 || y < -1 || z > 1 || z < -1)
		return (0);
	return (1);
}
