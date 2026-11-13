#include "grim_fetcher.h"

static void	apply_alpha(t_color *buf, t_ivec2 size, t_ubyte alpha);

t_img	*create_empty_image(const char *id, t_ivec2 size, t_ubyte alpha)
{
	t_img	*img;

	if (!id)
		return (0);
	img = calloc(1, sizeof(t_img));
	if (!img)
		return (0);
	img->id = strdup(id);
	set_ivec2(&img->size, size.x, size.y);
	img->cycle_len = 1;
	img->cycle = calloc(img->cycle_len, sizeof(t_color *));
	if (img->cycle)
		img->cycle[0] = calloc(img->size.x * img->size.y, sizeof(t_color));
	if (!img->id || !img->cycle || !img->cycle[0])
	{
		free_image(img, free);
		return (0);
	}
	apply_alpha(img->cycle[0], size, alpha);
	return (img);
}

static void	apply_alpha(t_color *buf, t_ivec2 size, t_ubyte alpha)
{
	int	i;
	int	len;

	if (!buf || !alpha)
		return ;
	i = 0;
	len = size.x * size.y;
	while (i < len)
		buf[i++].a = alpha;
	return ;
}
