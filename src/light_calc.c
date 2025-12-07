/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:46:10 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/25 18:50:34 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	light_calc(t_hit *hit, t_parse *p)
{
	t_color	diff;
	t_color	am;
	t_color	spec;

	diff = diffuse(hit, p);
	am = ambient(hit, p);
	spec = specular(hit, p);
	hit->pixel_color.r = fmin(255, diff.r + am.r + spec.r);
	hit->pixel_color.g = fmin(255, diff.g + am.g + spec.g);
	hit->pixel_color.b = fmin(255, diff.b + am.b + spec.b);
}

t_color	diffuse(t_hit *hit, t_parse *p)
{
	t_color	diff;
	double	intensity;

	if (dot(hit->normal, norm(sub(p->l_point, hit->colission))) > 0)
		intensity = fmax(0, dot(hit->normal, norm(sub(p->l_point,
							hit->colission))));
	else
		intensity = 0;
	if (is_in_shadow(hit, p))
		intensity = 0;
	diff.r = hit->pixel_color.r * (p->l_bright) * (p->l_color.r / 255)
		* intensity;
	diff.g = hit->pixel_color.g * (p->l_bright) * (p->l_color.g / 255)
		* intensity;
	diff.b = hit->pixel_color.b * (p->l_bright) * (p->l_color.b / 255)
		* intensity;
	return (diff);
}

t_color	ambient(t_hit *hit, t_parse *p)
{
	t_color	am;

	am.r = hit->pixel_color.r * (p->am_ratio) * (p->am_color.r / 255);
	am.g = hit->pixel_color.g * (p->am_ratio) * (p->am_color.g / 255);
	am.b = hit->pixel_color.b * (p->am_ratio) * (p->am_color.b / 255);
	return (am);
}

static t_color	specular_calc(t_hit *hit, t_parse *p, t_aux3 aux)
{
	t_color	spec;
	double	shininess;
	double	ks;
	double	spec_intensity;

	shininess = 100;
	ks = 0.5;
	spec_intensity = pow(fmax(0.0, dot(aux.r, aux.v)), shininess);
	if (is_in_shadow(hit, p))
		spec_intensity = 0;
	spec.r = p->l_color.r * p->l_bright * ks * spec_intensity;
	spec.g = p->l_color.g * p->l_bright * ks * spec_intensity;
	spec.b = p->l_color.b * p->l_bright * ks * spec_intensity;
	return (spec);
}

t_color	specular(t_hit *hit, t_parse *p)
{
	t_vec	l;
	t_vec	v;
	t_vec	r;
	t_aux3	aux3;

	l = norm(sub(p->l_point, hit->colission));
	v = norm(sub(p->cam->origin, hit->colission));
	r = sub(scale(2.0 * dot(hit->normal, l), hit->normal), l);
	aux3.l = l;
	aux3.v = v;
	aux3.r = r;
	return (specular_calc(hit, p, aux3));
}
