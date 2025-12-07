/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:59:23 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/20 17:53:17 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX_W 3840
#define MAX_H 2160
#define MIN_W 1600
#define MIN_H 1200
#define SCALE 1.333333
#define PI 3.14159

#pragma once

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef struct s_hit
{
	t_vec			colission;
	t_vec			normal;
	t_color			pixel_color;
	int				object;
	struct s_hit	*next;
}					t_hit;

typedef struct s_ray
{
	t_vec			or;
	t_vec			dir;
}					t_ray;

typedef struct s_sph
{
	t_vec			point;
	double			diam;
	t_color			color;
	t_color			pixel_color;
	int				is_colission;
	t_vec			colission;
	int				in;
	struct s_sph	*next;
}					t_sph;

typedef struct s_pl
{
	t_vec			point;
	t_vec			n_vector;
	t_vec			colission;
	t_color			color;
	t_color			pixel_color;
	struct s_pl		*next;
}					t_pl;

typedef struct s_cy
{
	t_vec			point;
	t_vec			colission;
	t_vec			n_vector;
	double			r;
	int				mcol;
	double			height;
	t_color			color;
	struct s_cy		*next;
}					t_cy;

typedef struct s_cam
{
	t_vec			origin;
	t_vec			fw;
	t_vec			up;
	t_vec			right;
	t_vec			center;
	t_vec			ver;
	t_vec			hor;
	t_vec			ll;
	double			fov;
	double			as_ratio;
	double			vp_h;
	double			vp_w;
}					t_cam;

typedef struct s_aux
{
	t_vec			point;
	t_vec			n_vector;
	double			diam;
	double			height;
	t_color			color;
}					t_aux;

typedef struct s_aux2
{
	t_vec			oc;
	double			rdv;
	double			ocv;
	t_vec			dt;
	t_vec			ot;
	double			a;
	double			b;
	double			c;
	double			t1;
	double			half_h;
	double			t2;
	double			t_max;
	double			condition;
	t_vec			top_p;
	t_vec			base_p;
}					t_aux2;

typedef struct s_aux3
{
	t_vec			r;
	t_vec			l;
	t_vec			v;
}					t_aux3;

typedef struct s_parse
{
	mlx_t			*data;
	mlx_image_t		*img;
	struct timeval	start;
	int				a;
	double			am_ratio;
	t_color			am_color;
	int				c;
	t_cam			*cam;
	int				l;
	t_vec			l_point;
	double			l_bright;
	t_color			l_color;
	t_hit			*hit;
	int				sp_count;
	t_sph			*sp;
	int				pl_count;
	t_pl			*pl;
	int				cy_count;
	t_cy			*cy;
	t_color			cy_color;
}					t_parse;

typedef struct s_render
{
	int				i;
	int				j;
	t_parse			*pr;
	int				finished;
}					t_render;

// ft_atod.c
double				ft_atod(char *str);

// gnl.c
char				*get_next_line(int fd);

// utils1.c
void				ft_debug_parsing(t_parse *p);
void				end_timer(struct timeval start);
int					ft_double_check(char *str);
int					ft_count_list(char	**list);

// ambient_parsing.c
int					ft_parse_ambient(char **spline, t_parse *program);
int					ft_init_t_color_am(t_parse *program, int r, int g, int b);

// camera_parsing.c
int					ft_parse_camera(char **sp, t_parse *program);
int					ft_init_cam_origin(t_parse *program, double x, double y,
						double z);
int					ft_init_cam_dir(t_parse *program, double x, double y,
						double z);
int					ft_init_cam_fov(t_parse *program, int fov);
void				ft_init_viewport(t_parse *p);

// light parsing.c
int					ft_parse_light(char **sp, t_parse *program);
int					ft_init_t_vec_li(t_parse *program, double x, double y,
						double z);
int					ft_init_t_color_li(t_parse *program, int r, int g, int b);

// parsing.c
int					ft_parse_line(char *line, t_parse *program);
char				*ft_format_line(char *str);
t_parse				*ft_read_file(int fd);
int					ft_check_extension(char *file);
int					ft_check_parsing(t_parse *p);
t_parse				*ft_parsing(int argc, char **argv);

// parsing_utils.c
int					ft_arg_count(char *str);
int					ft_space_count(char *str);
char				*ft_delete_spaces(char *str, char *dst);
int					ft_check_arg_count(char *str, int arg_count);
int					ft_check_argument(char *str);

// init.c
t_vec				ft_init_vec(double x, double y, double z);
t_color				ft_init_color(char **sp);
t_parse				*ft_init_parse(void);

// free.c
void				ft_free(char **sp);
t_parse				*ft_free_parsing(t_parse *p);

// sphere_lst.c
void				ft_sphadd_back(t_sph **lst, t_sph *new);
void				ft_sphadd_front(t_sph **lst, t_sph *new);
t_sph				*ft_sphnew(t_vec p, double d, t_color c);
int					ft_sphsize(t_sph *lst);
void				ft_free_sp(t_parse *p);

// sphere_parsing.c
int					ft_parse_sphere(char **sp, t_parse *p);
int					ft_check_color(char **sp);
int					ft_check_point(double x, double y, double z);
int					ft_init_t_color_sp(t_parse *p, int r, int g, int b);

// plane_lst.c
void				ft_free_pl(t_parse *p);
void				ft_pladd_back(t_pl **lst, t_pl *new);
void				ft_pladd_front(t_pl **lst, t_pl *new);
t_pl				*ft_plnew(t_vec p, t_vec n, t_color c);
int					ft_plsize(t_pl *lst);

// plane_parsing.c
int					ft_parse_plane(char **sp, t_parse *p);
int					ft_check_n_vector(double x, double y, double z);

// cylinder_lst.c
void				ft_free_cy(t_parse *p);
void				ft_cyadd_back(t_cy **lst, t_cy *new);
void				ft_cyadd_front(t_cy **lst, t_cy *new);
t_cy				*ft_cynew(t_aux params);
int					ft_cysize(t_cy *lst);

// cylinder_parsing.c
int					ft_parse_cylinder(char **sp, t_parse *p);

// t_vec_ops_1.c
t_vec				cross(t_vec a, t_vec b);
double				vlen(t_vec v);
t_vec				norm(t_vec v);
t_vec				scale(double f, t_vec v);
t_vec				add(t_vec a, t_vec b);
t_vec				sub(t_vec a, t_vec b);
double				dot(t_vec a, t_vec b);
double				dist(t_vec a, t_vec b);

// ray_tracer.c
t_ray				ft_calc_ray(int i, int j, t_parse *pr);
uint32_t			get_closest_color(t_parse *p);
int					ft_colission(t_ray ray, t_parse *pr, int x, int j);

// sphere_colission.c
int					sphere_colission(t_ray ray, t_parse *pr);
int					ft_there_is_colission_sp(t_ray ray, t_sph *sp);
double				ft_calc_det(t_ray ray, t_sph *sp);
int					ft_calc_intersection_sp(t_ray ray, t_sph *sp, double d);
int					ft_calc_point_sp_t1(double t1, double t2, t_ray ray,
						t_sph *sp);
int					ft_calc_point_sp_t2(double t1, double t2, t_ray ray,
						t_sph *sp);
int					ft_calc_point_sp(double t1, double t2, t_ray ray,
						t_sph *sp);
void				ft_printcolor(t_color c);

// sphere_light.c
void				light_calc(t_hit *hit, t_parse *p);
t_color				diffuse(t_hit *hit, t_parse *p);
t_color				ambient(t_hit *hit, t_parse *p);
t_color				specular(t_hit *hit, t_parse *p);

// shadow.c
int					sp_shadow(t_ray sh, t_parse *p);
int					sp_shadow_intersects(t_ray sh, t_sph *sp, int max);
int					is_in_shadow(t_hit *hit, t_parse *p);
int					pl_shadow(t_ray sh, t_parse *p);

// cy_shadows.c
int					cy_shadow_intersects(t_cy *cy, t_ray sh, double max);
int					cy_shadow(t_ray sh, t_parse *p);
int					check_t(t_aux2 aux, t_cy *cy);
int					check_intersects_cy(t_cy *cy, t_ray sh, t_aux2 aux);
int					check_base(t_aux2 aux, t_cy *cy, t_ray sh);

uint32_t			rgb_to_hex_alpha(t_color color);

// hit_lst.c
void				ft_free_hit(t_hit *p);
void				ft_hitadd_back(t_hit **lst, t_hit *new);
void				ft_hitadd_front(t_hit **lst, t_hit *new);
t_hit				*ft_hitnew(t_vec hit, t_color color, t_vec n, int m);
int					ft_hitsize(t_hit *lst);
void				print_hit_list(t_hit *hit_lst);

// plane_colission.c
int					plane_colission(t_ray ray, t_parse *pr);
int					ft_there_is_colission_pl(t_ray ray, t_pl *pl);

// cylinder_colission.c
t_vec				calc_normal_cy(t_cy *cy);
int					cylinder_colission(t_ray ray, t_parse *pr);
int					lateral_colission(t_ray ray, t_cy *cy);
int					calc_lateral_colission(t_ray ray, t_cy *cy, t_vec r);
int					cy_colission_point(t_ray ray, t_cy *cy, double t1,
						double t2);
int					cy_both_positive(t_ray ray, t_cy *cy, t_vec p1, t_vec p2);
int					last_case(t_ray ray, t_cy *cy, t_vec p1, t_vec p2);
int					ft_there_is_colission_cy(t_ray ray, t_cy *cy);

// cy_top_colission.c
int					top_colission(t_ray ray, t_cy *cy);
int					base_colission(t_ray ray, t_cy *cy);