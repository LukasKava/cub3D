/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:30:40 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/05 14:39:42 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * FUNCTION: (check_player_direction) checks that there would be a player.
 * 				That there would not be more than one player. And then it saves
 * 				the position of the player and its direction in the main struct.
 */
void	check_player_direction(t_main *main)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (main->map[i] != NULL)
	{
		while (main->map[i][x] != '\0')
		{
			if (main->map[i][x] == 'N' || main->map[i][x] == 'S' || \
				main->map[i][x] == 'E' || main->map[i][x] == 'W')
			{
				if (main->p_dir != '0')
					parsing_cleaning(main, NULL, MORE_THAN_ONE_PLAYER);
				main->p_dir = main->map[i][x];
				main->p_pos_x = x;
				main->p_pos_y = i;
			}
			x++;
		}
		x = 0;
		i++;
	}
	if (main->p_dir == '0')
		parsing_cleaning(main, NULL, PLAYER_DOES_NOT_EXIST);
}

void	initialize_rectangle(t_hive *h)
{
	h->r[0] = h->p_c_x - (5);
	h->r[1] = h->p_c_y - (5);
	h->r[2] = h->p_c_x + (5);
	h->r[3] = h->p_c_y - (5);
	h->r[4] = h->p_c_x - (5);
	h->r[5] = h->p_c_y + (5);
	h->r[6] = h->p_c_x + (5);
	h->r[7] = h->p_c_y + (5);
	h->p_c[0] = h->p_c_x - h->move;
	h->p_c[1] = h->p_c_y - h->move;
	h->p_c[2] = h->p_c_x + h->move;
	h->p_c[3] = h->p_c_y - h->move;
	h->p_c[4] = h->p_c_x - h->move;
	h->p_c[5] = h->p_c_y + h->move;
	h->p_c[6] = h->p_c_x + h->move;
	h->p_c[7] = h->p_c_y + h->move;
}

void	draw_p_dir_points(t_hive *h, int i, int x)
{
	initialize_rectangle(h);
	player_rotation(h, 'r', h->p_offset);
	player_rotation(h, 'c', h->p_offset);
	while (i < 4)
		h->line[i++] = h->r[x++];
	h->p_m[0] = (h->p_c[0] + h->p_c[2]) / 2;
	h->p_m[1] = (h->p_c[1] + h->p_c[3]) / 2;
	h->p_m[2] = (h->p_c[2] + h->p_c[6]) / 2;
	h->p_m[3] = (h->p_c[3] + h->p_c[7]) / 2;
	h->p_m[6] = (h->p_c[4] + h->p_c[6]) / 2;
	h->p_m[7] = (h->p_c[5] + h->p_c[7]) / 2;
	h->p_m[4] = (h->p_c[0] + h->p_c[4]) / 2;
	h->p_m[5] = (h->p_c[1] + h->p_c[5]) / 2;
}

void	choose_dir(t_hive *h)
{
	if (h->main->p_dir == 'N')
		h->p_offset = 0;
	else if (h->main->p_dir == 'E')
		h->p_offset = 90;
	else if (h->main->p_dir == 'S')
		h->p_offset = 180;
	else if (h->main->p_dir == 'W')
		h->p_offset = 270;
}

void	draw_player(t_hive *h, t_data *img)
{
	choose_dir(h);
	draw_p_dir_points(h, 0, 0);
	my_mlx_pixel_put(img, h->p_c_x, h->p_c_y, 3139839);
}
