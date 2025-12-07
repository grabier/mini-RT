/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_colission_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:16:58 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/17 20:47:33 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_calc_point_sp_t1(double t1, double t2, t_ray ray, t_sph *sp)
{
	t_vec	p1;

	if (t1 > 0 && t2 < 0)
	{
		p1 = add(ray.or, scale(t1, ray.dir));
		sp->colission = p1;
		sp->in = 1;
		return (1);
	}
	if (t2 > 0 && t1 < 0)
	{
		p1 = add(ray.or, scale(t2, ray.dir));
		sp->in = 1;
		sp->colission = p1;
	}
	return (1);
}

int	ft_calc_point_sp_t2(double t1, double t2, t_ray ray, t_sph *sp)
{
	t_vec	p1;

	if (t2 > 0 && t1 < 0)
	{
		p1 = add(ray.or, scale(t2, ray.dir));
		sp->in = 1;
		sp->colission = p1;
	}
	return (1);
}
