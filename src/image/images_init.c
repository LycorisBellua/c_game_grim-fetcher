#include "grim_fetcher.h"

static int	fetch_image(t_img **dst, const char *id);
static int	check_map_images(void);

/*
	Loads every image, then keeps the ones drawn on every frame at hand, so
	that they aren't searched by ID each time.
*/
int	init_images(void)
{
	if (!update_image_array(&man, IMG_JSON_DEFAULT))
		return (put_error(E_FAIL_JSON, IMG_JSON_DEFAULT, 0));
	if (!fetch_image(&man.img_cursor, ID_CURSOR)
		|| !fetch_image(&man.img_font, ID_FONT)
		|| !fetch_image(&man.img_ground, ID_GROUND)
		|| !fetch_image(&man.img_wall_hor_one, ID_WALL_HOR_ONE)
		|| !fetch_image(&man.img_wall_hor_three, ID_WALL_HOR_THREE)
		|| !fetch_image(&man.img_wall_hor_one_cliff, ID_WALL_HOR_ONE_CLIFF)
		|| !fetch_image(&man.img_wall_ver_two, ID_WALL_VER_TWO)
		|| !fetch_image(&man.img_soul_gui, ID_SOUL_GUI)
		|| !check_map_images()
		|| !create_background()
		|| !add_red_version_of_ground())
		return (0);
	add_outline_to_font(man.img_font);
	return (1);
}

void	deinit_images(void)
{
	free_images(&man);
	free_image(man.img_background, free);
	free_image(man.img_red_ground, free);
	man.img_background = 0;
	man.img_cursor = 0;
	man.img_font = 0;
	man.img_ground = 0;
	man.img_red_ground = 0;
	man.img_wall_hor_one = 0;
	man.img_wall_hor_three = 0;
	man.img_wall_hor_one_cliff = 0;
	man.img_wall_ver_two = 0;
	man.img_soul_gui = 0;
	return ;
}

static int	fetch_image(t_img **dst, const char *id)
{
	*dst = get_image(&man, id);
	if (!*dst)
		return (put_error(E_NO_IMG, id, 0));
	return (1);
}

/* The images looked up by ID while setting a map or turning the player. */
static int	check_map_images(void)
{
	size_t		i;
	t_img		*img;
	const char	*ids[] = {"wall_hor_three_doorframe_closed",
		"wall_hor_three_doorframe_open", "soul_idle", "dog_idle_down_right",
		"dog_idle_down_left", "dog_idle_up_right", "dog_idle_up_left",
		"slime_blue_idle_down_right", "slime_green_idle_down_right", 0};

	i = 0;
	while (ids[i])
	{
		if (!fetch_image(&img, ids[i]))
			return (0);
		++i;
	}
	return (1);
}
