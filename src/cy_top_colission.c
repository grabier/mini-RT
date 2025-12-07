/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_top_colission.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:31:01 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/17 19:39:50 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	top_colission(t_ray ray, t_cy *cy)
{
	t_vec	top;
	t_vec	p;
	t_vec	aux;
	double	t;

	top = add(cy->point, scale(cy->height / 2, cy->n_vector));
	t = (dot(sub(top, ray.or), cy->n_vector)) / dot(ray.dir, cy->n_vector);
	if (t > 0)
	{
		p = add(ray.or, scale(t, ray.dir));
		aux = sub(p, top);
		if (dot(aux, aux) <= (cy->r * cy->r))
		{
			cy->colission = p;
			cy->mcol = 1;
			return (1);
		}
	}
	return (0);
}

int	base_colission(t_ray ray, t_cy *cy)
{
	t_vec	top;
	t_vec	p;
	t_vec	aux;
	double	t;

	top = sub(cy->point, scale(cy->height / 2, cy->n_vector));
	t = (dot(sub(top, ray.or), cy->n_vector)) / dot(ray.dir, cy->n_vector);
	if (t > 0)
	{
		p = add(ray.or, scale(t, ray.dir));
		aux = sub(p, top);
		if (dot(aux, aux) <= (cy->r * cy->r))
		{
			cy->colission = p;
			cy->mcol = 2;
			return (1);
		}
	}
	return (0);
}
