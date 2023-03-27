/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:19:31 by lkavalia          #+#    #+#             */
/*   Updated: 2023/03/27 12:25:06 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO: ENUMS for readability

void	ft_exiterr(int err)
{
	if (err == NOT_ENOUGH_ARGS)
		ft_putstr_fd(RED "Not enough arguments!\n" B, 2);
	else if (err == INVALID_ARGS)
		ft_putstr_fd(RED "Invalid arguments!\n" B, 2);
	else if (err == WRONG_FILE_EXTENSION)
		ft_putstr_fd(RED "Invalid file Ext! Only files with [.cub] Ext!\n" B, 2);
	else if (err == FILE_IS_NOT_THERE)
		ft_putstr_fd(RED "File does not exist!\n" B, 2);
	else if (err == INCORECT_FILE_CONFIG)
		ft_putstr_fd(RED "Map has to be the last in config file!\n" B, 2);
	else if (err == CUB_CONTAINS_TRASH)
		ft_putstr_fd(RED ".cub file contains trash characters!\n" B, 2);
	else if (err == MISSING_ELEMENT_PATH)
		ft_putstr_fd(RED "Texure path is not specified!\n" B, 2);
	else if (err == FOUND_ELEMENT_TRASH)
		ft_putstr_fd(RED "Please check the texure field!\n" B, 2);
	else if (err == INCORECT_COLOR_VAL)
		ft_putstr_fd(RED "Invalid color: 0-255,0-255,0-255\n" B, 2);
	else if (err == TAB_IN_MAP_FOUND)
		ft_putstr_fd(RED "Check Map there are tabs!\n" B, 2);
	else if (err == MAP_NOT_CLOSED)
		ft_putstr_fd(RED "Map is not closed!\n" B, 2);
	else if (err == WRONG_INFO_IN_MAP)
		ft_putstr_fd(RED "ERROR map possible characters: 'NSEW10 '!\n" B, 2);
	else if (err == EMPTY_LINE_IN_MAP)
		ft_putstr_fd(RED "Empty line beetween the map lines!\n" B, 2);
	else if (err == MORE_THAN_ONE_PLAYER)
		ft_putstr_fd(RED "There is more than 1 player!\n" B, 2);
	else if (err == MAP_IS_NOT_CLOSED)
		ft_putstr_fd(RED "Map is not closed!\n" B, 2);
	else if (err == PLAYER_DOES_NOT_EXIST)
		ft_putstr_fd(RED "Player does not exist in the map!\n" B, 2);
	exit (err);
}

//Checks if the file extension is .cub
static void	check_file_extension(char *filename)
{
	int		i;
	char	*file_ex;

	i = ft_strlen(filename);
	file_ex = ft_substr(filename, i - 4, 4);
	printf("[1] Check the extension: %s\n", file_ex);
	if (ft_strncmp(file_ex, ".cub", ft_strlen(".cub")) != 0)
	{
		free(file_ex);
		ft_exiterr(WRONG_FILE_EXTENSION);
	}
	free(file_ex);
}

static void	check_for_tabs(t_main *main, char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\t')
		i++;
	if (buffer[i] != '\0' && buffer[i] == '\t')
		parsing_cleaning(main, buffer, TAB_IN_MAP_FOUND);
}

static void	check_file_config(t_main *main)
{
	bool	map_found;
	char	*buffer;

	map_found = false;
	buffer = get_next_line(main->file_fd);
	while (buffer != NULL)
	{
		check_for_tabs(main, buffer);
		if (map_found == false)
			map_found = map_fragment_found(buffer);
		printf("check1: %d ", map_found);
		printf("buffer: %s", buffer);
		if (component_found(buffer) == true && map_found == true)
		{
			free(buffer);
			close(main->file_fd);
			ft_exiterr(INCORECT_FILE_CONFIG);
		}
		find_trash(main, buffer);
		free(buffer);
		buffer = get_next_line(main->file_fd);
	}
}

void	check_basic_errors(t_main *main, int argc, char **argv)
{
	if (argc != 2)
		ft_exiterr(NOT_ENOUGH_ARGS);
	check_file_extension(argv[1]);
	open_the_file(main, argv);
	check_file_config(main);
	close(main->file_fd);
	open_the_file(main, argv);
}
