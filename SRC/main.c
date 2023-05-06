/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:30:05 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/06 21:20:10 by lkavalia         ###   ########.fr       */
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

void	player_rotation(t_hive *h, int offset)
{
	double	s;
	double	c;
	double	tmp_x;

	tmp_x = 0;
	if (fmod(h->angle + offset, 90) == 0 || fmod(h->angle + offset, 180) == 0)
	{
		s = (int)sin((h->angle + offset) * RADIAN);
		c = (int)cos((h->angle + offset) * RADIAN);
	}
	else
	{
		s = sin((h->angle + offset) * RADIAN);
		c = cos((h->angle + offset) * RADIAN);
	}
	tmp_x = h->p_c[0];
	player_center_rotation(h, tmp_x, c, s);
}

int	render(t_hive *h)
{
	h->data->img = mlx_new_image(h->vars->mlx, S_WIDTH, S_HEIGHT);
	h->data->addr = mlx_get_data_addr(h->data->img, &h->data->bits_per_pixel, \
	&h->data->line_length, &h->data->endian);
	draw_player(h);
	draw_2d_rays(h);
	mlx_put_image_to_window(h->vars->mlx, h->vars->win, h->data->img, 0, 0);
	mlx_destroy_image(h->vars->mlx, h->data->img);
	return (0);
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
