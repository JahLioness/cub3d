/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:13:37 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/20 14:20:48 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_condition_map(char **map, int i, int j)
{
	if (map[i][j] && (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
			&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'))
		return (1);
	return (0);
}

int	ft_check_char(char **map, int i, int j)
{
	if ((i - 1 >= 0 && ft_condition_map(map, i - 1, j)) || i - 1 < 0)
		return (1);
	else if ((j - 1 >= 0 && ft_condition_map(map, i, j - 1)) || j - 1 < 0)
		return (1);
	else if (ft_condition_map(map, i + 1, j) || !map[i + 1][j])
		return (1);
	else if (ft_condition_map(map, i, j + 1) || !map[i][j + 1])
		return (1);
	return (0);
}

int	ft_check_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\t')
				return (1);
			else if (map[i][j] == '0')
			{
				if (ft_check_char(map, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

// if (i - 1 >= 0 && map[i - 1][j] && ft_is_whitespaces(map[i - 1][j]))
// 	return (1);
// if (map[i + 1][j] && ft_is_whitespaces(map[i + 1][j]))
// 	return (1);
// if (j - 1 >= 0 && map[i][j - 1] && ft_is_whitespaces(map[i][j - 1]))
// 	return (1);
// if (map[i][j  + 1] && ft_is_whitespaces(map[i][j + 1]))
// 	return (1);
