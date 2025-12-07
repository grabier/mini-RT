/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:26:21 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/25 18:50:15 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_cylinder_point(char **sp_aux, t_aux *a)
{
	if (!sp_aux[0] || !sp_aux[1] || !sp_aux[2])
		return (printf("cy point invalid\n"), ft_free(sp_aux), 0);
	if (!ft_check_point(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]),
			ft_atod(sp_aux[2])))
		return (printf("cy point invalid\n"), ft_free(sp_aux), 0);
	a->point = ft_init_vec(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]),
			ft_atod(sp_aux[2]));
	return (1);
}

int	ft_parse_cylinder_vector(char **sp_aux, t_aux *a)
{
	if (!sp_aux[0] || !sp_aux[1] || !sp_aux[2])
		return (printf("cy normal vector invalid\n"), ft_free(sp_aux), 0);
	if (!ft_check_n_vector(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]),
			ft_atod(sp_aux[2])))
		return (printf("cy normal vector invalid\n"), ft_free(sp_aux), 0);
	a->n_vector = norm(ft_init_vec(ft_atod(sp_aux[0]), ft_atod(sp_aux[1]),
				ft_atod(sp_aux[2])));
	return (1);
}

int	ft_parse_cylinder(char **sp, t_parse *p)
{
	t_aux	a;
	char	**sp_aux;

	sp_aux = ft_split(sp[1], ',');
	if (!ft_parse_cylinder_point(sp_aux, &a))
		return (ft_free(sp), 0);
	ft_free(sp_aux);
	sp_aux = ft_split(sp[2], ',');
	if (!ft_parse_cylinder_vector(sp_aux, &a))
		return (ft_free(sp), 0);
	ft_free(sp_aux);
	a.diam = ft_atod(sp[3]);
	if (a.diam <= 0 || fabs(a.diam - 2.232323) < 0.0001)
		return (printf("cy diam invalid\n"), ft_free(sp), 0);
	a.height = ft_atod(sp[4]);
	if (a.height <= 0 || fabs(a.height - 2.232323) < 0.0001)
		return (printf("cy height invalid\n"), ft_free(sp), 0);
	sp_aux = ft_split(sp[5], ',');
	if (!ft_check_color(sp_aux))
		return (printf("cy color invalid\n"), ft_free(sp_aux), ft_free(sp), 0);
	a.color = ft_init_color(sp_aux);
	ft_cyadd_back(&p->cy, ft_cynew(a));
	p->cy_count++;
	return (ft_free(sp_aux), ft_free(sp), 1);
}
