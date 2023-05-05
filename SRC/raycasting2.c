/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:17:44 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/05 14:19:13 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_horizontal_wall(t_hive *h)
{
	int	wallx;
	int	wally;

	wallx = (h->current_hor_x - TILE) / (TILE);
	if (h->quadrant == 3 || h->quadrant == 4)
		wally = (h->current_hor_y - TILE) / (TILE);
	else
		wally = (h->current_hor_y - TILE) / (TILE) - 1;
	if (wally >= 0 && wally < h->main->height && wallx >= 0 && \
		wallx < (int)ft_strlen(h->main->map[wally]))
	{
		if (h->main->map[wally][wallx] == '1')
			return (1);
	}
	else
		return (2);
	return (0);
}

int	check_vertical_wall(t_hive *h)
{
	int	wallx;
	int	wally;

	if (h->quadrant == 1 || h->quadrant == 4)
		wallx = (h->current_ver_x - TILE) / (TILE);
	else
		wallx = (h->current_ver_x - TILE) / (TILE) - 1;
	wally = (h->current_ver_y - TILE) / TILE;
	if (wally >= 0 && wally < h->main->height && \
		wallx >= 0 && wallx < (int)ft_strlen(h->main->map[wally]))
	{
		if (h->main->map[wally][wallx] == '1')
			return (1);
	}
	else
		return (2);
	return (0);
}

void	count_horizontal_scaling(t_hive *h)
{
	h->horizontal_x_scaling = fabs(TILE / tan(h->real_angle * RADIAN));
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 90)
		h->horizontal_x_scaling = 10000000;
}

void	count_vertical_scaling(t_hive *h)
{
	h->vertical_y_scaling = fabs(tan(h->real_angle * RADIAN) * TILE);
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 0)
		h->vertical_y_scaling = 10000000;
}

double	calculate_dist_draw(t_hive *h, int hor_hit, int ver_hit)
{
	double	magnitude_horizontal_v;
	double	magnitude_vertical_v;

	magnitude_horizontal_v = sqrt(fabs(pow(h->current_hor_x - h->p_c_x, 2)) + \
									fabs(pow(h->current_hor_y - h->p_c_y, 2)));
	magnitude_vertical_v = sqrt(fabs(pow(h->current_ver_x - h->p_c_x, 2)) + \
									fabs(pow(h->current_ver_y - h->p_c_y, 2)));
	h->x_ray = false;
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 90)
		magnitude_horizontal_v = magnitude_vertical_v + 10;
	if (fabs(remainder(h->angle + h->p_offset, 180)) == 0)
		magnitude_vertical_v = magnitude_horizontal_v + 10;
	if (ver_hit == 2)
		magnitude_vertical_v = magnitude_horizontal_v + 10;
	if (hor_hit == 2)
		magnitude_horizontal_v = magnitude_vertical_v + 10;
	if (magnitude_horizontal_v < magnitude_vertical_v)
	{
		h->x_ray = true;
		return (magnitude_horizontal_v);
	}
	return (magnitude_vertical_v);
}
