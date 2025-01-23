/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:59:17 by ede-cola          #+#    #+#             */
/*   Updated: 2025/01/23 16:35:48 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>

typedef struct s_map
{
	int			height;
	int			width;
	char		**map_tab;
	int			**map_int;
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
	double		pos_y;
	double		pos_x;
	double		dir_y;
	double		dir_x;
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
int				ft_clean_init_player(t_data *map_data);
int				mlx_start(t_data *map_data);
int				mlx_window_init(t_data *map_data);

/*		UTILS		*/
size_t			ft_longest_line(char **map);
char			*ft_get_textures_path(char *path, char *entry);
char			*ft_join_to_comb_empty(char *line, size_t longest_line);

/*		FREE		*/
int				ft_free_img(t_mlx *mlx, int n);
int				ft_free_data(t_data *map_data);

/*		CHECK_TEXTURES		*/
int				ft_check_textures(t_data *map_data);
t_img			*ft_init_img(t_mlx *mlx, char *path);
int				ft_check_rgb(t_data *map_data);

/*		CONVERT_MAP			*/
int				**ft_convert_map(char **map);

/*		RAYCAST_UTILS		*/
int				ft_get_player_pos(t_data *map_data);


/*		TEST		*/
void	raycasting(t_data *map_data);

#endif