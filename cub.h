/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:17 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/14 13:12:39 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./minilibx-linux/mlx.h"
# include "libft/libft.h"

typedef struct s_map
{
	int			height;
	int			width;
	char		**map_tab;
}				t_map;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			endian;
	int			bpp;
	int			line_len;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	int			pos_y;
	int			pos_x;
	int			dir_y;
	int			dir_x;
}				t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		*img[4];
}				t_mlx;

typedef struct s_data
{
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
	char		*texture_f;
	char		*texture_c;
	char		*texture_n;
	char		*texture_s;
	char		*texture_e;
	char		*texture_w;

}				t_data;

/*		PARSE				*/
char			**ft_read_map(char *map);
int				ft_check_map(char **map);
int				ft_get_data(t_data *map_data, char **file);

/*		PARSE_MAP*/
int				ft_check_map_closed(char **map);
int				ft_check_player(char **map);

/*		INIT		*/
int				ft_clean_init_data(t_data *map_data);
int				mlx_start(t_data *map_data);
int				mlx_window_init(t_data *map_data);

/*		UTILS		*/
int				ft_longest_line(char **map);
char			*ft_get_textures_path(char *path, char *entry);

/*		FREE		*/
int				ft_free_img(t_mlx *mlx, int n);
int				ft_free_data(t_data *map_data);

/*		CHECK_TEXTURES		*/
int				ft_check_textures(t_data *map_data);
t_img			*ft_init_img(t_mlx *mlx, char *path);
int				ft_check_rgb(t_data *map_data);

/*		CONVERT_MAP			*/
int				**ft_convert_map(char **map);

#endif