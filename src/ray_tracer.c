/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:53:11 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/17 20:29:15 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_ray	ft_calc_ray(int i, int j, t_parse *pr)
{
	double	u;
	double	v;
	t_vec	dir;
	t_ray	ray;

	u = (i + 0.5) / MIN_W;
	v = (j + 0.5) / MIN_H;
	dir = add(add(pr->cam->ll, scale(u, pr->cam->hor)), scale(v, pr->cam->ver));
	ray.or = pr->cam->origin;
	ray.dir = norm(sub(dir, pr->cam->origin));
	return (ray);
}

uint32_t	get_closest_color(t_parse *p)
{
	t_hit	*aux;
	t_hit	*closest;
	double	distance;

	aux = p->hit;
	closest = NULL;
	distance = __DBL_MAX__;
	while (aux)
	{
		if (distance > vlen(sub(aux->colission, p->cam->origin)))
		{
			distance = vlen(sub(aux->colission, p->cam->origin));
			closest = aux;
		}
		aux = aux->next;
	}
	light_calc(closest, p);
	return (rgb_to_hex_alpha(closest->pixel_color));
}

int	ft_colission(t_ray ray, t_parse *pr, int x, int j)
{
	int	intersects;

	intersects = 0;
	ft_free_hit(pr->hit);
	pr->hit = NULL;
	intersects += sphere_colission(ray, pr);
	intersects += plane_colission(ray, pr);
	intersects += cylinder_colission(ray, pr);
	if (pr->hit)
		mlx_put_pixel(pr->img, x, j, get_closest_color(pr));
	return (intersects);
}
