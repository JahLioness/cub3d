/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:17 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/03 23:46:55 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft/libft.h"

typedef struct s_data
{
	char	**map;
	char	*texture_f;
	char	*texture_c;
	char	*texture_n;
	char	*texture_s;
	char	*texture_e;
	char	*texture_w;

}			t_data;

char		**ft_read_map(char *map);
int			ft_check_map(char **map);
int			ft_get_data(t_data *map_data, char **file);
int			ft_clean_init_data(t_data *map_data);
int			ft_free_data(t_data *map_data);

#endif