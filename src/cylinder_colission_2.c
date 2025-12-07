/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_colission_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:51:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/17 20:51:48 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	cy_colission_point(t_ray ray, t_cy *cy, double t1, double t2)
{
	t_vec	p1;
	t_vec	p2;

	p1 = add(ray.or, scale(t1, ray.dir));
	p2 = add(ray.or, scale(t2, ray.dir));
	if (t2 > 0 && t1 < 0)
	{
		p1 = add(ray.or, scale(t2, ray.dir));
		if ((dot(sub(p1, cy->point), cy->n_vector)) >= ((-1 * cy->height) / 2)
			&& (dot(sub(p1, cy->point), cy->n_vector)) <= (cy->height / 2))
		{
			cy->colission = p2;
			cy->mcol = 0;
		}
		return (1);
	}
	if (t1 > 0 && t2 > 0)
	{
		if (cy_both_positive(ray, cy, p1, p2))
			return (1);
		return (0);
	}
	return (0);
}

int	cy_both_positive(t_ray ray, t_cy *cy, t_vec p1, t_vec p2)
{
	if ((dot(sub(p1, cy->point), cy->n_vector)) < ((-1 * cy->height) / 2)
		|| (dot(sub(p1, cy->point), cy->n_vector)) > cy->height / 2)
	{
		if ((dot(sub(p2, cy->point), cy->n_vector)) <= ((-1 * cy->height) / 2)
			|| (dot(sub(p2, cy->point), cy->n_vector)) >= cy->height / 2)
			return (0);
	}
	if ((dot(sub(p1, cy->point), cy->n_vector)) < ((-1 * cy->height) / 2)
		|| (dot(sub(p1, cy->point), cy->n_vector)) > cy->height / 2)
	{
		cy->colission = p2;
		cy->mcol = 0;
		return (1);
	}
	if ((dot(sub(p2, cy->point), cy->n_vector)) <= ((-1 * cy->height) / 2)
		&& (dot(sub(p2, cy->point), cy->n_vector)) >= cy->height / 2)
	{
		cy->colission = p1;
		cy->mcol = 0;
		return (1);
	}
	return (last_case(ray, cy, p1, p2));
}

int	last_case(t_ray ray, t_cy *cy, t_vec p1, t_vec p2)
{
	if (vlen(sub(p1, ray.or)) > vlen(sub(p2, ray.or)))
		cy->colission = p2;
	else
		cy->colission = p1;
	cy->mcol = 0;
	return (1);
}
