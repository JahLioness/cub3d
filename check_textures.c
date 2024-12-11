/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:32 by ede-cola          #+#    #+#             */
/*   Updated: 2024/12/11 18:05:04 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_img	*ft_init_img(t_mlx *mlx, char *path)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(mlx->mlx, path, &img->width, &img->height);
	if (!img->img)
		return (free(img), NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (free(img->img), free(img), NULL);
	return (img);
}

int	ft_check_textures(t_data *map_data)
{
	map_data->mlx->img[0] = ft_init_img(map_data->mlx, map_data->texture_n);
	if (!map_data->mlx->img[0])
		return (1);
	map_data->mlx->img[1] = ft_init_img(map_data->mlx, map_data->texture_s);
	if (!map_data->mlx->img[1])
		return (1);
	map_data->mlx->img[2] = ft_init_img(map_data->mlx, map_data->texture_w);
	if (!map_data->mlx->img[2])
		return (1);
	map_data->mlx->img[3] = ft_init_img(map_data->mlx, map_data->texture_e);
	if (!map_data->mlx->img[3])
		return (1);
	return (0);
}

int	ft_check_rgb(t_data *map_data)
{
	int	i;
	char	**tab;

	i = 0;
	while (map_data->texture_c[i])
	{
		if ((map_data->texture_c[i] != ','
				&& !ft_isdigit(map_data->texture_c[i]))
			|| (map_data->texture_f[i] != ','
				&& !ft_isdigit(map_data->texture_f[i])))
			return (1);
		i++;
	}
	tab = ft_split(map_data->texture_c, ',');
	if (ft_tab_len(tab) > 3 || ft_tab_len(tab) < 3)
		return (ft_free_tab(tab), 1);
	i = 0;
	while (tab[i])
	{
		if (ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
			return (ft_free_tab(tab), 1);
		i++;
	}
	ft_free_tab(tab);
	tab = ft_split(map_data->texture_f, ',');
	if (ft_tab_len(tab) > 3 || ft_tab_len(tab) < 3)
		return (ft_free_tab(tab), 1);
	i = 0;
	while (tab[i])
	{
		if (ft_atoi(tab[i]) < 0 || ft_atoi(tab[i]) > 255)
			return (ft_free_tab(tab), 1);
		i++;
	}
	ft_free_tab(tab);
	return (0);
}
