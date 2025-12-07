/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:02:19 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/24 10:28:45 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	esc_keyhook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void	ft_create_images(t_render *r)
{
	int		j;
	int		i;
	t_ray	ray;

	i = r->i;
	j = r->j;
	while (j < MIN_H)
	{
		i = 0;
		while (i < MIN_W)
		{
			ray = ft_calc_ray(i, j, r->pr);
			ft_colission(ray, r->pr, i, j);
			i++;
		}
		j++;
	}
	r->i = i;
	r->j = j;
}

void	ft_render_hook(void *param)
{
	t_render	*r;
	int			batch;
	int			j;
	int			bj;

	r = (t_render *)param;
	batch = 10;
	j = r->j;
	bj = 0;
	while (bj < batch && j < MAX_H)
	{
		ft_create_images(r);
		bj++;
		j++;
	}
	r->j = j;
}

void	ft_render_loop(t_render *r)
{
	if (r->finished == 0)
		ft_render_hook(r);
	if (r->i == MIN_W)
		r->finished = 1;
	mlx_image_to_window(r->pr->data, r->pr->img, 0, 0);
	mlx_key_hook(r->pr->data, &esc_keyhook, r->pr->data);
	mlx_loop(r->pr->data);
}

int	main(int argc, char **argv)
{
	t_parse		*program;
	t_render	render;

	program = ft_parsing(argc, argv);
	if (!program)
		return (1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	program->data = mlx_init(MIN_W, MIN_H, "Hello world!", 1);
	mlx_set_window_limit(program->data, MIN_W, MIN_H, MAX_W, MAX_H);
	program->img = mlx_new_image(program->data, MIN_W, MIN_H);
	render.i = 0;
	render.j = 0;
	render.pr = program;
	render.finished = 0;
	ft_render_loop(&render);
	mlx_delete_image(program->data, program->img);
	mlx_terminate(program->data);
	ft_free_parsing(program);
	return (EXIT_SUCCESS);
}
