#include "grim_fetcher.h"

t_img	*get_image(t_man *man, const char *id)
{
	size_t	i;

	if (man->images)
	{
		i = 0;
		while (man->images[i])
		{
			if (!strcmp(man->images[i]->id, id))
				return (man->images[i]);
			++i;
		}
	}
	return (0);
}
