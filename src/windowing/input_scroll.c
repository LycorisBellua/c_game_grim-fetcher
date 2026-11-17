#include "grim_fetcher.h"

/*
	Trackpads scroll by fractions of a step, so they're added up until they 
	make whole steps. The zoom levels are 1, 2, 3, 5, 7 and 9.
*/
void	scroll_callback(GLFWwindow *window, double x_offset, double y_offset)
{
	static float	scrolled;
	int				steps;

	(void)window;
	(void)x_offset;
	scrolled += (float)y_offset;
	steps = (int)scrolled;
	scrolled -= steps;
	while (steps > 0 && g_man.zoom < MAP_ZOOM_MAX)
	{
		g_man.zoom = clamp(g_man.zoom + 1 + (g_man.zoom >= 3), 1, MAP_ZOOM_MAX);
		--steps;
	}
	while (steps < 0 && g_man.zoom > 1)
	{
		g_man.zoom -= 1 + (g_man.zoom > 3);
		++steps;
	}
	return ;
}
