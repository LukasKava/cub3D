/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 23:13:36 by lkavalia          #+#    #+#             */
/*   Updated: 2023/05/06 23:16:31 by lkavalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * FUNCTION: (check_file_extension) checks that the file
 * 				extension would be .cub
 */
void	check_file_extension(char *filename)
{
	int		i;
	char	*file_ex;

	i = ft_strlen(filename);
	file_ex = ft_substr(filename, i - 4, 4);
	if (ft_strncmp(file_ex, ".cub", ft_strlen(".cub")) != 0)
	{
		free(file_ex);
		ft_exiterr(WRONG_FILE_EXTENSION);
	}
	free(file_ex);
}
