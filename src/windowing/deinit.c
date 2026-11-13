#include "grim_fetcher.h"

void	deinit(t_man *man)
{
	if (!man)
		return ;
	if (man->gl_loaded)
	{
		free_shader_program(man);
		free_mesh();
	}
	free_uniform(man);
	free_frame(man);
	deinit_images(man);
	free_map_filenames(man);
	game_deinit(man);
	glfwTerminate();
	man->window = 0;
	man->gl_loaded = 0;
	return ;
}

void	game_deinit(t_man *man)
{
	free(man->map.cells);
	man->map.cells = 0;
	list_clear(&man->clicked_path, 0);
	man->clicked_path = 0;
	return ;
}
