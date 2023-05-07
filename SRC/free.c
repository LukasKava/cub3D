/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:28:17 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/07 17:23:21 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_the_hive(t_hive *h)
{
	if (h->main != NULL)
		free(h->main);
	if (h->b != NULL)
		free(h->b);
	if (h->wall_tex != NULL)
	{
		if (h->wall_tex->texture_north != NULL)
			free(h->wall_tex->texture_north);
		if (h->wall_tex->texture_south != NULL)
			free(h->wall_tex->texture_south);
		if (h->wall_tex->texture_west != NULL)
			free(h->wall_tex->texture_west);
		if (h->wall_tex->texture_east != NULL)
			free(h->wall_tex->texture_east);
		free(h->wall_tex);
	}
}

void	parsing_cleaning(t_hive *h, char *arr, int err)
{
	if (arr != NULL)
		free(arr);
	clear_the_main_struct(h->main);
	clear_the_hive(h);
	ft_exiterr(err);
}

int	close_game(t_hive *hive)
{
	mlx_destroy_window(hive->vars->mlx, hive->vars->win);
	clear_the_main_struct(hive->main);
	exit(0);
}

void	clear_the_main_struct(t_main *main)
{
	int	i;

	i = 0;
	if (main->file_fd > 2)
		close(main->file_fd);
	if (main->north_t != NULL)
		free(main->north_t);
	if (main->south_t != NULL)
		free(main->south_t);
	if (main->west_t != NULL)
		free(main->west_t);
	if (main->east_t != NULL)
		free(main->east_t);
	if (main->map != NULL)
	{
		while (main->map[i] != NULL)
			free(main->map[i++]);
		free(main->map);
	}
}
