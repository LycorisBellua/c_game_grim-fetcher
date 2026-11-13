#include "grim_fetcher.h"

/*
	Trackpads scroll by fractions of a step, so they're added up until they
	make whole steps.
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
	if (g_man.zoom <= 3)
		g_man.zoom = clamp(g_man.zoom + steps, 1, 10);
	else
		g_man.zoom = clamp(g_man.zoom + steps * 2, 1, 10);
	return ;
}
