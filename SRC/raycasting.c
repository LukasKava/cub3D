/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:32:54 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/06 20:12:22 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rest_horizontal(t_hive *h, int start_tile_pos_y, int step)
{
	h->current_hor_len = TILE / sin(h->real_angle * RADIAN);
	if (h->quadrant == 4 || h->quadrant == 3)
		h->current_hor_y = start_tile_pos_y + (TILE) + ((TILE) * step);
	else
		h->current_hor_y = start_tile_pos_y - ((TILE) * step);
	if (h->quadrant == 3 || h->quadrant == 2)
		h->current_hor_x -= h->horizontal_x_scaling;
	else
		h->current_hor_x += h->horizontal_x_scaling;
}

void	rest_vertical(t_hive *h, int start_tile_pos_x, int step)
{
	h->current_ver_len = TILE / cos(h->real_angle * RADIAN);
	h->current_ver_x = start_tile_pos_x + (TILE) * step + (TILE);
	if (h->quadrant == 3 || h->quadrant == 4)
		h->current_ver_y += h->vertical_y_scaling;
	else
		h->current_ver_y -= h->vertical_y_scaling;
	if (h->quadrant == 3 || h->quadrant == 2)
		h->current_ver_x = start_tile_pos_x - (TILE) * step;
}

void	raycasting(t_hive *h, int start_tile_pos_x, int start_tile_pos_y)
{
	int		step;
	int		hor_hit;
	int		ver_hit;

	step = 1;
	ver_hit = 0;
	hor_hit = 0;
	first_horizontal(h, start_tile_pos_x, start_tile_pos_y);
	first_vertical(h, start_tile_pos_x, start_tile_pos_y);
	hor_hit = check_horizontal_wall(h);
	ver_hit = check_vertical_wall(h);
	while (hor_hit == 0)
	{
		rest_horizontal(h, start_tile_pos_y, step++);
		hor_hit = check_horizontal_wall(h);
	}
	step = 1;
	while (ver_hit == 0)
	{
		rest_vertical(h, start_tile_pos_x, step++);
		ver_hit = check_vertical_wall(h);
	}
	if (ver_hit != 0 && hor_hit != 0)
		h->shortest_dist_to_wall = calculate_dist_draw(h, hor_hit, ver_hit);
}

void	draw_2d_rays(t_hive *h)
{
	int		a;
	double	fov;
	int		start_tile_pos_x;
	int		start_tile_pos_y;

	a = 0;
	fov = -30;
	h->angle -= 30;
	h->current_tile_pos_x = (h->p_c_x - TILE) / TILE;
	h->current_tile_pos_y = (h->p_c_y - TILE) / TILE;
	start_tile_pos_x = (TILE + (h->current_tile_pos_x * TILE));
	start_tile_pos_y = (TILE + (h->current_tile_pos_y * TILE));
	while (a < S_WIDTH)
	{
		decide_quadrant(h);
		h->real_angle = fabs((double)90 - remainder(h->angle + \
									(double)h->p_offset, (double)180));
		count_vertical_scaling(h);
		count_horizontal_scaling(h);
		raycasting(h, start_tile_pos_x, start_tile_pos_y);
		draw_3d(h, a++, fov);
		h->angle += h->one_colum_increase;
		fov += h->one_colum_increase;
	}
	h->angle -= 30;
}
