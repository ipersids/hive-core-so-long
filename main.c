/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2024/12/23 18:46:17 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;
	int		check;

	if (2 != argc)
		so_exit_error(ERR_AGRC);

	so_map_init(&map);
	check = so_validate_level(argv[1], &map);
	if (check)
		so_exit_error(check);
	so_game_init(&game, &map);

	so_mlx_init(&game);
	if (!so_set_layout(&game))
	{
		so_free_arr(game.lvl.map, game.lvl.row);
		return(123);
	}
	/// TESTING >>>
	mlx_image_to_window(game.mlx, game.layout[WHITEGRND], 0, 0);
	mlx_image_to_window(game.mlx, game.layout[BACKGRND], 0, 0);
	mlx_image_to_window(game.mlx, game.layout[FOREGRND], 0, 0);

	game.pl.player = so_load_sprite(
		"textures/kenney/characters/yellow_character.png", \
		game.mlx, game.sprite_size \
	);
	if (!game.pl.player)
	{
		mlx_terminate(game.mlx);
		so_free_arr(map.map_arr, map.row);
		return -1;
	}
	mlx_image_to_window(game.mlx, game.pl.player, game.pl.x * game.sprite_size, game.pl.y * game.sprite_size);

	if (!so_set_coin_animation(&game))
	{
		printf("free\n");
		so_destroy_game(&game);
		return -1;
	}

	if (!so_set_num_animation(&game))
	{
		printf("free\n");
		so_destroy_game(&game);
		return -1;
	}

	mlx_loop_hook(game.mlx, so_set_coin_hook, &game);
	mlx_loop_hook(game.mlx, so_set_counter_hook, &game);
	mlx_loop_hook(game.mlx, so_set_esc_hook, &game);
	mlx_close_hook(game.mlx, so_set_close_hook, &game);
	mlx_key_hook(game.mlx, so_set_move_hook, &game);
	/// TESTING END <<<

	mlx_loop(game.mlx);
	so_destroy_game(&game);
	return (0);
}
