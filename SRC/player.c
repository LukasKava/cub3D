/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:30:40 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/07 17:51:32 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * FUNCTION: (check_player_direction) checks that there would be a player.
 * 				That there would not be more than one player. And then it saves
 * 				the position of the player and its direction in the main struct.
 */
void	check_player_direction(t_hive *h, t_main *main)
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
					parsing_cleaning(h, NULL, MORE_THAN_ONE_PLAYER);
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
		parsing_cleaning(h, NULL, PLAYER_DOES_NOT_EXIST);
}

void	initialize_rectangle(t_hive *h)
{
	h->p_c[0] = h->p_c_x - h->move;
	h->p_c[1] = h->p_c_y - h->move;
	h->p_c[2] = h->p_c_x + h->move;
	h->p_c[3] = h->p_c_y - h->move;
	h->p_c[4] = h->p_c_x - h->move;
	h->p_c[5] = h->p_c_y + h->move;
	h->p_c[6] = h->p_c_x + h->move;
	h->p_c[7] = h->p_c_y + h->move;
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

void	draw_player(t_hive *h)
{
	initialize_rectangle(h);
	player_rotation(h, h->p_offset);
	h->p_m[0] = (h->p_c[0] + h->p_c[2]) / 2;
	h->p_m[1] = (h->p_c[1] + h->p_c[3]) / 2;
	h->p_m[2] = (h->p_c[2] + h->p_c[6]) / 2;
	h->p_m[3] = (h->p_c[3] + h->p_c[7]) / 2;
	h->p_m[6] = (h->p_c[4] + h->p_c[6]) / 2;
	h->p_m[7] = (h->p_c[5] + h->p_c[7]) / 2;
	h->p_m[4] = (h->p_c[0] + h->p_c[4]) / 2;
	h->p_m[5] = (h->p_c[1] + h->p_c[5]) / 2;
}
