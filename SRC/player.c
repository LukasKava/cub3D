/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:30:40 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/06 21:09:42 by lkavalia         ###   ########.fr       */
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
	h->p_c[0] = h->p_c_x - h->move;
	h->p_c[1] = h->p_c_y - h->move;
	h->p_c[2] = h->p_c_x + h->move;
	h->p_c[3] = h->p_c_y - h->move;
	h->p_c[4] = h->p_c_x - h->move;
	h->p_c[5] = h->p_c_y + h->move;
	h->p_c[6] = h->p_c_x + h->move;
	h->p_c[7] = h->p_c_y + h->move;
}

void	draw_p_dir_points(t_hive *h)
{
	initialize_rectangle(h);
	player_rotation(h,  h->p_offset);
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

void	draw_player(t_hive *h)
{
	choose_dir(h);
	draw_p_dir_points(h);
}
