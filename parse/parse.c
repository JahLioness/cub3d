/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:06 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/24 22:38:52 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

int	ft_get_textures(char **file, t_data *data, int i, int j)
{
	if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'N')
		data->texture_n = ft_get_textures_path(file[i], "NO");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'S')
		data->texture_s = ft_get_textures_path(file[i], "SO");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'W')
		data->texture_w = ft_get_textures_path(file[i], "WE");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'E')
		data->texture_e = ft_get_textures_path(file[i], "EA");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'F')
		data->texture_f = ft_get_textures_path(file[i], "F");
	else if (!ft_is_whitespaces(file[i][j]) && file[i][j] == 'C')
		data->texture_c = ft_get_textures_path(file[i], "C");
	return (0);
}

void	ft_get_map(char **file, int *i, int j, t_data *data)
{
	int		len;
	size_t	max_width;

	if (!ft_check_line(file[*i]) && !ft_is_whitespaces(file[*i][j])
		&& data->texture_n != NULL)
	{
		len = *i;
		while (file[len])
			len++;
		data->map = ft_calloc(1, sizeof(t_map));
		data->map->map_tab = ft_calloc((len - *i) + 1, sizeof(char *));
		len = 0;
		max_width = ft_longest_line(file);
		while (file[*i])
		{
			if (ft_strlen(file[*i]) < max_width)
				data->map->map_tab[len] = ft_join_to_comb_empty(file[*i],
						max_width);
			else
				data->map->map_tab[len] = ft_strdup(file[*i]);
			len++;
			(*i)++;
		}
		data->map->map_tab[len] = NULL;
	}
}

int	ft_check_data(t_data *data)
{
	return (data->texture_n != NULL && data->map != NULL
		&& data->texture_f != NULL && data->texture_n != NULL
		&& data->texture_s != NULL && data->texture_e != NULL
		&& data->texture_w != NULL);
}

int	ft_get_data(t_data *data, char **file)
{
	int	i;
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
		ft_get_textures(file, data, i, j);
		ft_get_map(file, &i, j, data);
		if (file[i])
			i++;
	}
	return (ft_check_data(data));
}
