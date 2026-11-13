#include "grim_fetcher.h"

static int	init(t_man *man);
static int	game_init(t_man *man, char *map_path);

t_man	g_man;

int	main(void)
{
	t_color	c_black_opaque;

	memset(&g_man, 0, sizeof(t_man));
	c_black_opaque = get_color_rgba(0, 0, 0, 255);
	if (!init(&g_man))
	{
		deinit(&g_man);
		return (EXIT_FAILURE);
	}
	while (!glfwWindowShouldClose(g_man.window))
	{
		set_dt_and_fps(&g_man);
		advance_all_image_cycles(&g_man);
		fill_frame(&g_man.frame, c_black_opaque);
		render(&g_man);
		display_frame(&g_man);
	}
	deinit(&g_man);
	return (EXIT_SUCCESS);
}

int	reload_game(t_man *man, int next_map)
{
	if (next_map && !man->map_filenames[man->map_index + 1])
		return (0);
	game_deinit(man);
	if (next_map)
		++man->map_index;
	return (game_init(man, man->map_filenames[man->map_index]));
}

static int	init(t_man *man)
{
	t_ivec2	size;

	memset(man, 0, sizeof(t_man));
	man->vsync = 1;
	man->zoom = 5;
	set_ivec2(&size, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!create_window(man, TITLE, size, ASPECT_RATIO) || !init_frame(man))
		return (0);
	man->gui_scale = man->res.res.y / 360;
	if (man->gui_scale < 1)
		man->gui_scale = 1;
	set_map_filenames(man);
	if (!man->map_filenames)
		return (put_error(E_NO_MAP, MAP_DIR, 0));
	if (!init_images(man)
		|| !game_init(man, man->map_filenames[man->map_index]))
		return (0);
	init_input_handling(man);
	return (1);
}

static int	game_init(t_man *man, char *map_path)
{
	memset(&man->player, 0, sizeof(t_player));
	memset(&man->map, 0, sizeof(t_map));
	man->clicked_path = 0;
	man->click_pending = 0;
	set_ivec2(&man->cursor, -1, -1);
	set_ivec2(&man->click_pos, -1, -1);
	change_game_state(man, GAME_STATE_PLAY);
	return (!!set_map_and_player(man, map_path));
}
