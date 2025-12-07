/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_shadows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:06:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/17 19:39:47 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_t(t_aux2 aux, t_cy *cy)
{
	double	t_candidates[2];
	double	condition;
	int		i;
	double	t;

	(void)cy;
	t_candidates[0] = aux.t1;
	t_candidates[1] = aux.t2;
	i = -1;
	while (++i < 2)
	{
		t = t_candidates[i];
		if (t > 0.0001 && t < aux.t_max)
		{
			condition = aux.ocv + t * aux.rdv;
			if ((-aux.half_h) <= condition && condition <= aux.half_h)
				return (1);
		}
	}
	return (0);
}

int	check_base(t_aux2 aux, t_cy *cy, t_ray sh)
{
	double	t;
	t_vec	q;

	t = dot(sub(aux.top_p, sh.or), cy->n_vector) / dot(sh.dir, cy->n_vector);
	if (0 < t && t < aux.t_max)
	{
		q = add(sh.or, scale(t, sh.dir));
		if (dist(q, aux.top_p) <= cy->r)
			return (1);
	}
	t = dot(sub(aux.base_p, sh.or), cy->n_vector) / dot(sh.dir, cy->n_vector);
	if (0 < t && t < aux.t_max)
	{
		q = add(sh.or, scale(t, sh.dir));
		if (dist(q, aux.base_p) <= cy->r)
			return (1);
	}
	return (0);
}

int	check_intersects_cy(t_cy *cy, t_ray sh, t_aux2 aux)
{
	double	b_2;

	(void)sh;
	b_2 = aux.b * aux.b;
	if ((b_2 - (4 * aux.a * aux.c)) < 0)
		return (0);
	aux.t1 = ((-1 * aux.b) - sqrt(b_2 - (4 * aux.a * aux.c))) / (2 * aux.a);
	aux.t2 = ((-1 * aux.b) + sqrt(b_2 - (4 * aux.a * aux.c))) / (2 * aux.a);
	if (check_t(aux, cy))
		return (1);
	if (check_base(aux, cy, sh))
		return (1);
	return (0);
}

int	cy_shadow_intersects(t_cy *cy, t_ray sh, double max)
{
	t_aux2	aux;

	aux.oc = sub(sh.or, cy->point);
	aux.rdv = dot(sh.dir, cy->n_vector);
	aux.ocv = dot(aux.oc, cy->n_vector);
	aux.dt = sub(sh.dir, scale(aux.rdv, cy->n_vector));
	aux.ot = sub(aux.oc, scale(aux.ocv, cy->n_vector));
	aux.a = dot(aux.dt, aux.dt);
	aux.b = 2 * dot(aux.dt, aux.ot);
	aux.c = dot(aux.ot, aux.ot) - (cy->r * cy->r);
	aux.t_max = max;
	aux.half_h = cy->height / 2;
	aux.top_p = add(cy->point, scale(aux.half_h, cy->n_vector));
	aux.base_p = sub(cy->point, scale(aux.half_h, cy->n_vector));
	if (check_intersects_cy(cy, sh, aux))
		return (1);
	return (0);
}

int	cy_shadow(t_ray sh, t_parse *p)
{
	t_cy	*aux;
	double	max;

	aux = p->cy;
	while (aux)
	{
		max = vlen(sub(p->l_point, sh.or));
		if (cy_shadow_intersects(aux, sh, max))
			return (1);
		aux = aux->next;
	}
	return (0);
}
