/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:06 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/04 00:46:29 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_count_line(char *map)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (0);
	lines = 1;
	line = get_next_line(fd, 0);
	if (!line)
		return (close(fd), 0);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd, 0);
	}
	free(line);
	close(fd);
	return (lines);
}

char	**ft_read_map(char *map)
{
	int		fd;
	int		size;
	int		i;
	char	*line;
	char	**ret;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (NULL);
	size = ft_count_line(map);
	if (!size)
		return (NULL);
	ret = ft_calloc(size, sizeof(char *));
	if (!ret)
		return (close(fd), NULL);
	i = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		ret[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd, 0);
	}
	ret[i] = NULL;
	return (free(line), close(fd), ret);
}

int	ft_check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 32 && map[i][j] != '\t' && map[i][j] != '0'
				&& map[i][j] != '1' && map[i][j] != 'N' && map[i][j] != 'S'
				&& map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '\n' && str[i] != 32 && str[i] != '\t'
			&& str[i] != '0' && str[i] != 'N' && str[i] != 'S' && str[i] != 'W'
			&& str[i] != 'E')
			return (1);
		i++;
	}
	return (0);
}

int	ft_get_data(t_data *map_data, char **file)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (ft_is_whitespaces(file[i][j]))
		{
			j++;
			if (!file[i][j] && file[i])
			{
				i++;
				j = 0;
			}
		}
		if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'N')
			map_data->texture_n = ft_strdup(file[i]);
		else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'S')
			map_data->texture_s = ft_strdup(file[i]);
		else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'W')
			map_data->texture_w = ft_strdup(file[i]);
		else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'E')
			map_data->texture_e = ft_strdup(file[i]);
		else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'F')
			map_data->texture_f = ft_strdup(file[i]);
		else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'C')
			map_data->texture_c = ft_strdup(file[i]);
		else if (!ft_check_line(file[i]) && !ft_is_whitespaces(file[i][j]))
		{
			len = i;
			while (file[len])
				len++;
			map_data->map = ft_calloc((len - i) + 1, sizeof(char *));
			len = 0;
			while (file[i])
			{
				map_data->map[len] = ft_strdup(file[i]);
				len++;
				i++;
			}
			map_data->map[len] = NULL;
		}
		if (file[i])
			i++;
	}
	if (map_data->texture_n != NULL)
		return (1);
	else
		return (0);
}
