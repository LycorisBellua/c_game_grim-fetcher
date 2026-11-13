#include "grim_fetcher.h"

void	mouse_callback(GLFWwindow *window, int button, int action, int mods)
{
	(void)window;
	(void)mods;
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			list_clear(&g_man.clicked_path, 0);
			g_man.click = 1;
		}
		else if (action == GLFW_RELEASE)
			g_man.click = 0;
		if (action == GLFW_PRESS && g_man.cursor.x >= 0)
		{
			set_ivec2(&g_man.click_pos, g_man.cursor.x, g_man.cursor.y);
			g_man.click_pending = 1;
		}
	}
	return ;
}

void	cursor_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (!window_pos_to_view(&g_man, xpos, ypos, &g_man.cursor))
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else if (g_man.img_cursor)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	return ;
}
