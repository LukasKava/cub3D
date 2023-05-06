/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbas <mabbas@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:30:05 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/06 20:40:31 by mabbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < S_WIDTH && y < S_HEIGHT && x > 0 && y > 0)
	{
		dst = data->addr + (y * data->line_length + x * \
												(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	close_game(t_hive *hive)
{
	mlx_destroy_window(hive->vars->mlx, hive->vars->win);
	clear_the_main_struct(hive->main);
	exit(0);
}

void	move_player(t_hive *h, int indentifier)
{
	if (indentifier == W_KEY)
	{
		h->p_c_x = h->p_m[0];
		h->p_c_y = h->p_m[1];
	}
	if (indentifier == S_KEY)
	{
		h->p_c_x = h->p_m[6];
		h->p_c_y = h->p_m[7];
	}
	if (indentifier == A_KEY)
	{
		h->p_c_x = h->p_m[4];
		h->p_c_y = h->p_m[5];
	}
	if (indentifier == D_KEY)
	{
		h->p_c_x = h->p_m[2];
		h->p_c_y = h->p_m[3];
	}
}

int	key_hook(int keycode, t_hive *hive)
{
	if (keycode == ESC_KEY)
		close_game(hive);
	if (keycode == LEFT_KEY)
		hive->angle += 5;
	else if (keycode == RIGHT_KEY)
		hive->angle -= 5;
	else
		move_player(hive, keycode);
	return (0);
}

void	player_center_rotation(t_hive *h, int tmp_x, double c, double s)
{
	tmp_x = h->p_c[0];
	h->p_c[0] = ((h->p_c[0] - h->p_c_x) * c - \
					(h->p_c[1] - h->p_c_y) * s) + h->p_c_x;
	h->p_c[1] = ((tmp_x - h->p_c_x) * s + \
					(h->p_c[1] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->p_c[2];
	h->p_c[2] = ((h->p_c[2] - h->p_c_x) * c - \
					(h->p_c[3] - h->p_c_y) * s) + h->p_c_x;
	h->p_c[3] = ((tmp_x - h->p_c_x) * s + \
					(h->p_c[3] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->p_c[4];
	h->p_c[4] = ((h->p_c[4] - h->p_c_x) * c - \
					(h->p_c[5] - h->p_c_y) * s) + h->p_c_x;
	h->p_c[5] = ((tmp_x - h->p_c_x) * s + \
					(h->p_c[5] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->p_c[6];
	h->p_c[6] = ((h->p_c[6] - h->p_c_x) * c - \
					(h->p_c[7] - h->p_c_y) * s) + h->p_c_x;
	h->p_c[7] = ((tmp_x - h->p_c_x) * s + \
					(h->p_c[7] - h->p_c_y) * c) + h->p_c_y;
}

void	rectangle_rotation(t_hive *h, int tmp_x, double c, double s)
{
	tmp_x = h->r[0];
	h->r[0] = ((h->r[0] - h->p_c_x) * c - \
				(h->r[1] - h->p_c_y) * s) + h->p_c_x;
	h->r[1] = ((tmp_x - h->p_c_x) * s + \
				(h->r[1] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->r[2];
	h->r[2] = ((h->r[2] - h->p_c_x) * c - \
				(h->r[3] - h->p_c_y) * s) + h->p_c_x;
	h->r[3] = ((tmp_x - h->p_c_x) * s + \
				(h->r[3] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->r[4];
	h->r[4] = ((h->r[4] - h->p_c_x) * c - \
				(h->r[5] - h->p_c_y) * s) + h->p_c_x;
	h->r[5] = ((tmp_x - h->p_c_x) * s + \
				(h->r[5] - h->p_c_y) * c) + h->p_c_y;
	tmp_x = h->r[6];
	h->r[6] = ((h->r[6] - h->p_c_x) * c - \
				(h->r[7] - h->p_c_y) * s) + h->p_c_x;
	h->r[7] = ((tmp_x - h->p_c_x) * s + \
				(h->r[7] - h->p_c_y) * c) + h->p_c_y;
}

void	player_rotation(t_hive *h, char indentifier, int offset)
{
	double	s;
	double	c;	
	int		tmp_x;

	tmp_x = 0;
	s = sin((h->angle + offset) * RADIAN);
	c = cos((h->angle + offset) * RADIAN);
	if (indentifier == 'r')
	{
		rectangle_rotation(h, tmp_x, c, s);
		return ;
	}
	tmp_x = h->p_c[0];
	player_center_rotation(h, tmp_x, c, s);
}

int	render(t_hive *h)
{
	h->data->img = mlx_new_image(h->vars->mlx, S_WIDTH, S_HEIGHT);
	h->data->addr = mlx_get_data_addr(h->data->img, &h->data->bits_per_pixel, \
	&h->data->line_length, &h->data->endian);
	draw_2d_rays(h);
	draw_player(h, h->data);
	mlx_put_image_to_window(h->vars->mlx, h->vars->win, h->data->img, 0, 0);
	mlx_destroy_image(h->vars->mlx, h->data->img);
	return (0);
}

void	load_assets(t_hive *h)
{
	if (h->main->north_t != NULL)
		load_texure(h->wall_tex->texture_north, h, h->main->north_t);
	else
		load_texure(h->wall_tex->texture_north, h, D_NO);
	if (h->main->south_t != NULL)
		load_texure(h->wall_tex->texture_south, h, h->main->south_t);
	else
		load_texure(h->wall_tex->texture_south, h, D_SO);
	if (h->main->east_t != NULL)
		load_texure(h->wall_tex->texture_east, h, h->main->east_t);
	else
		load_texure(h->wall_tex->texture_east, h, D_EA);
	if (h->main->west_t != NULL)
		load_texure(h->wall_tex->texture_west, h, h->main->west_t);
	else
		load_texure(h->wall_tex->texture_west, h, D_WE);
	if (h->main->ground == -1)
		h->main->ground = D_F;
	if (h->main->roof == -1)
		h->main->roof = D_C;
}

void play_music(void)
{
	system ("afplay -v 100 -t 10 ./assets/intro.wav");
}

int	main(int argc, char **argv)
{
	t_hive	*hive;

	hive = ft_calloc(sizeof(t_hive), 1);
	initialize_hive(hive);
	initialize_main(hive->main);
	check_basic_errors(hive->main, argc, argv);
	parsing(hive->main, argv);
	initialize_mlx(hive->data, hive->vars);
	load_assets(hive);
	play_music();
	hive->p_c_x = TILE + (hive->main->p_x * (TILE)) + ((TILE) / 2);
	hive->p_c_y = TILE + (hive->main->p_y * (TILE)) + ((TILE) / 2);
	mlx_hook(hive->vars->win, 2, (1L) << 0, &key_hook, hive);
	mlx_hook(hive->vars->win, 17, 0L, close_game, hive);
	mlx_loop_hook(hive->vars->mlx, &render, hive);
	mlx_loop(hive->vars->mlx);
	return (0);
}
