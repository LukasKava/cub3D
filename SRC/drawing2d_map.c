/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:12:11 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/05 14:34:30 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_tile(t_data *img, int start_x, int start_y, char tile)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	if (tile == '1')
// 	{
// 		while (y <= 16)
// 		{
// 			while (x <= 16)
// 				my_mlx_pixel_put(img, start_x + x++, start_y + y, 16711680);
// 			x = 0;
// 			y++;
// 		}
// 		return ;
// 	}
// 	x = 1;
// 	y = 1;
// 	while (y < 16)
// 	{
// 		while (x < 16)
// 			my_mlx_pixel_put(img, start_x + x++, start_y + y, 8421504);
// 		x = 1;
// 		y++;
// 	}
// }

// void	draw_flat_map(t_main *main, t_data *img)
// {
// 	int	x;
// 	int	y;
// 	int	start_x;
// 	int	start_y;

// 	x = 0;
// 	y = 0;
// 	start_x = 16;
// 	start_y = 16;
// 	while (main->map[y] != NULL)
// 	{
// 		while (main->map[y][x] != '\0')
// 		{
// 			if (main->map[y][x] == '1' || main->map[y][x] == '0')
// 				draw_tile(img, start_x, start_y, main->map[y][x]);
// 			else if (main->map[y][x] == 'N' || main->map[y][x] == 'S'
//					|| main->map[y][x] == 'W' || main->map[y][x] == 'E')
// 				draw_tile(img, start_x, start_y, main->map[y][x]);
// 			x++;
// 			start_x += 16;
// 		}
// 		y++;
// 		start_y += 16;
// 		x = 0;
// 		start_x = 16;
// 	}
// }
