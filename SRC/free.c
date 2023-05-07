/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:28:17 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/08 00:25:16 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freeing_hive(t_hive *hive, int error_code)
{
	free(hive->data);
	free(hive->vars);
	free(hive->b);
	free(hive->wall_tex->texture_east);
	free(hive->wall_tex->texture_north);
	free(hive->wall_tex->texture_south);
	free(hive->wall_tex->texture_west);
	free(hive->wall_tex);
	parsing_cleaning(hive->main, NULL, error_code);
	free(hive);
}

void	parsing_cleaning(t_main *main, char *arr, int err)
{
	if (arr != NULL)
		free(arr);
	clear_the_main_struct(main);
	free(main);
	ft_exiterr(err);
}

int	close_game(t_hive *hive)
{
	mlx_destroy_window(hive->vars->mlx, hive->vars->win);
	freeing_hive(hive, 2000);
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
