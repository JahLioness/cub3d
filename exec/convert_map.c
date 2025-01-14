/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:05:02 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/14 13:46:28 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	**ft_convert_map(char **map)
{
	int	**tab;
	int	i;
	int	j;

	tab = ft_calloc(ft_tab_len(map), sizeof(int *));
	if (!tab)
		return (NULL);
	i = 0;
	while(map[i])
	{
		tab[i] = ft_calloc(ft_strlen(map[i]), sizeof(int));
		if (!tab[i])
		{
			while (i--)
				free(tab[i]);
			return(NULL);
		}
		j = 0;
		while(map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == '\n')
				break ;
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				tab[i][j] = 3;
			else if (!ft_is_whitespaces(map[i][j]))
				tab[i][j] = ft_atoi_char(map[i][j]);
			else
				tab[i][j] = 2;
			j++;
		}
		i++;		
	}
	return (tab);
}
