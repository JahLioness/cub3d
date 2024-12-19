/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:13:37 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/19 18:19:10 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_check_map_closed(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if ((i - 1 >= 0 && map[i - 1][j] && ((map[i - 1][j] != '1'
						&& map[i - 1][j] != '0' && map[i - 1][j] != 'N' && map[i
						- 1][j] != 'S' && map[i - 1][j] != 'E' && map[i
						- 1][j] != 'W') || ft_is_whitespaces(map[i - 1][j]))) || !map[i - 1][j])
					return (1);
				else if ((j - 1 >= 0 && map[i][j - 1] && ((map[i][j - 1] != '1'
						&& map[i][j - 1] != '0' && map[i][j - 1] != 'N'
						&& map[i][j - 1] != 'S' && map[i][j - 1] != 'E'
						&& map[i][j - 1] != 'W') || ft_is_whitespaces(map[i][j - 1]))) || !map[i][j - 1])
					return (1);
				else if ((map[i + 1][j] && ((map[i + 1][j] != '1'
						&& map[i + 1][j] != '0' && map[i + 1][j] != 'N' && map[i
						+ 1][j] != 'S' && map[i + 1][j] != 'E' && map[i
						+ 1][j] != 'W') || ft_is_whitespaces(map[i + 1][j]))) || !map[i + 1][j])
					return (1);
				else if ((map[i][j + 1] && ((map[i][j + 1] != '1'
						&& map[i][j + 1] != '0' && map[i][j + 1] != 'N'
						&& map[i][j + 1] != 'S' && map[i][j + 1] != 'E'
						&& map[i][j + 1] != 'W') || ft_is_whitespaces(map[i][j + 1]))) || !map[i][j + 1])
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
