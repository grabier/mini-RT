/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aehrl <aehrl@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:06:00 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/17 21:36:32 by aehrl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_parse_problem(int mode, char **sp1, char **sp2)
{
	if (mode == 0)
		printf("Error\nlight parsing\n");
	if (mode == 1)
		printf("light point invalid\n");
	if (mode == 2)
		printf("light ratio invalid\n");
	if (mode == 3)
		printf("light color invalid\n");
	ft_free(sp1);
	ft_free(sp2);
	return (0);
}

int	ft_parse_light(char **sp, t_parse *program)
{
	char	**sp_aux;
	char	**sp_aux2;
	double	f;

	sp_aux = ft_split(sp[1], ',');
	if (ft_count_list(sp_aux) != 3)
		return (ft_parse_problem(0, sp, sp_aux));
	f = ft_atod(sp_aux[0]);
	if (!ft_init_t_vec_li(program, f, ft_atod(sp_aux[1]), ft_atod(sp_aux[2])))
		return (ft_parse_problem(1, sp, sp_aux));
	f = ft_atod(sp[2]);
	if (f < 0.0 || f > 1.0 || fabs(f - 2.232323) < 0.0001)
		return (ft_parse_problem(2, sp, sp_aux));
	program->l_bright = f;
	sp_aux2 = ft_split(sp[3], ',');
	if (!ft_check_color(sp_aux2))
		return (ft_free(sp_aux2), ft_parse_problem(3, sp, sp_aux));
	if (!ft_init_t_color_li(program, ft_atoi(sp_aux2[0]), ft_atoi(sp_aux2[1]),
			ft_atoi(sp_aux2[2])))
		return (ft_free(sp_aux2), ft_parse_problem(3, sp, sp_aux));
	if (sp[4] != NULL || sp_aux[3] != NULL || sp_aux2[3] != NULL)
		return (ft_free(sp_aux), ft_free(sp_aux2), ft_free(sp), 0);
	program->l++;
	return (ft_free(sp_aux), ft_free(sp_aux2), ft_free(sp), 1);
}

int	ft_init_t_vec_li(t_parse *program, double x, double y, double z)
{
	if (fabs(x - 2.232323) < 0.0001 || fabs(y - 2.232323) < 0.0001 || fabs(z
			- 2.232323) < 0.0001)
		return (0);
	program->l_point.x = x;
	program->l_point.y = y;
	program->l_point.z = z;
	return (1);
}

int	ft_init_t_color_li(t_parse *program, int r, int g, int b)
{
	if (r > 255 || g > 255 || b > 255 || r < 0 || g < 0 || b < 0)
		return (0);
	program->l_color.r = (unsigned char)r;
	program->l_color.g = (unsigned char)g;
	program->l_color.b = (unsigned char)b;
	return (1);
}
