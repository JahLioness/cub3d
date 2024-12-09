/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:05:54 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/09 18:10:58 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_longest_line(char **map)
{
	int		i;
	size_t	width;

	i = 0;
	width = 0;
	while (map[i])
	{
		if (width < ft_strlen(map[i]))
			width = ft_strlen(map[i]);
		i++;
	}
	return (width);
}

char	*ft_get_textures_path(char *path, char *entry)
{
	int		i;
	char	*ret;

	i = 0;
	while (ft_is_whitespaces(path[i]))
		i++;
	if (!ft_strncmp(path + i, entry, ft_strlen(entry)))
		i += ft_strlen(entry);
	if (!ft_is_whitespaces(path[i]))
		return(NULL);
	while (ft_is_whitespaces(path[i]))
		i++;
	ret = ft_strdup(path + i);
	return (ret);
}
