#include "grim_fetcher.h"

static void	draw_background(t_color *buf, int width, int height,
				unsigned int seed);
static void	set_color(t_color *buf, int i, float rng, t_color color);

/*
	The background is made at the frame size divided by the GUI scale (rounded 
	up) and drawn scaled, so the sky looks the same at any resolution.
*/
int	create_background(t_man *man)
{
	t_ivec2	size;
	int		s;

	s = man->gui_scale;
	set_ivec2(&size, (man->res.res.x + s - 1) / s, (man->res.res.y + s - 1)
		/ s);
	man->img_background = create_empty_image(ID_BACKGROUND, size, 255);
	if (!man->img_background)
		return (put_error(E_FAIL_MEM, 0, 0));
	draw_background(man->img_background->cycle[0], size.x, size.y, 4);
	return (1);
}

void	render_background(t_man *man)
{
	t_ivec2	pos;

	set_ivec2(&pos, 0, 0);
	draw_image(man, man->img_background, pos);
	return ;
}

static void	draw_background(t_color *buf, int width, int height,
		unsigned int seed)
{
	t_ivec2	p;
	t_vec2	center;
	t_vec2	point;
	float	max_dist;
	float	factor;

	set_vec2(&center, width / 2, height / 2);
	set_vec2(&point, 0, 0);
	max_dist = dist(center, point);
	p.y = 0;
	while (p.y < height)
	{
		p.x = 0;
		while (p.x < width)
		{
			set_vec2(&point, p.x, p.y);
			factor = sqrt_approx(dist(point, center) / max_dist);
			set_color(buf, p.y * width + p.x, rng_minmax(&seed, 0, width)
				/ (float)width, get_color_rgba(108 * (1 - factor), 0,
				255 * (1 - factor), 255));
			++p.x;
		}
		++p.y;
	}
	return ;
}

static void	set_color(t_color *buf, int i, float rng, t_color color)
{
	t_color	sky;
	t_color	star;

	if (rng < 0.001f)
	{
		sky.a = 0xFF;
		sky.r = color.r;
		sky.g = color.g;
		sky.b = color.b;
		star.a = 0x7F;
		star.r = 0xE3;
		star.g = 0xDE;
		star.b = 0xD1;
		color = alpha_blending(sky, star);
		color.a = 255;
		buf[i] = color;
	}
	else if (rng < 0.002f)
		buf[i] = get_color_rgba(255, 255, 255, 255);
	else
		buf[i] = color;
	return ;
}
