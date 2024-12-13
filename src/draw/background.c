/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:20:07 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/14 00:10:06 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* --------------------- Private function prototypes ----------------------- */

static const char	*get_bg_path(t_background_type type);
static mlx_image_t	**get_bg_img(mlx_t *mlx, uint32_t sp_size, \
									mlx_image_t **bg);
static void			destroy_images(mlx_t *mlx, uint32_t i, \
									mlx_image_t **images);

/* --------------------------- Public Functions ---------------------------- */

mlx_image_t	*so_draw_background(mlx_t *mlx, uint32_t sp_size, char **map)
{
	mlx_image_t	**images;
	int32_t		x;
	int32_t		y;
	mlx_image_t	*bg;

	images = get_bg_img(mlx, sp_size, &bg);
	if (!images)
		return (NULL);
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == MAP_CODE[1])
				so_draw_img(bg, images[WALL], x * sp_size, y * sp_size);
			else
				so_draw_img(bg, images[GROUND], x * sp_size, y * sp_size);
			x++;
		}
		y++;
	}
	destroy_images(mlx, BG_MAX, images);
	return (bg);
}

/* ------------------- Private Function Implementation --------------------- */

static const char	*get_bg_path(t_background_type type)
{
	static char	list[BG_MAX][100] = {
		"textures/crate.png",
		"textures/floor_plants.png"
	};

	return (list[type]);
}

static mlx_image_t **get_bg_img(mlx_t *mlx, uint32_t sp_size, mlx_image_t **bg)
{
    static mlx_image_t	*images[BG_MAX];
	int 				i;

    i = 0;
	while (i < BG_MAX)
	{
        images[i] = so_load_sprite(get_bg_path(i), mlx, sp_size);
        if (!images[i]) {
            destroy_images(mlx, i, images);
            return NULL;
        }
		i++;
    }
    *bg = mlx_new_image(mlx, mlx->width, mlx->height);
    if (!*bg) {
        destroy_images(mlx, BG_MAX, images);
        return NULL;
    }
	ft_memset((*bg)->pixels, 255, (*bg)->width * (*bg)->height * RGBA);
    return images;
}

static void destroy_images(mlx_t *mlx, uint32_t i, mlx_image_t **images)
{
    for (uint32_t j = 0; j < i; j++) {
        if (images[j]) {
            mlx_delete_image(mlx, images[j]);
            images[j] = NULL;
        }
    }
}