#include "lem_in.h"

char	*skip_comments()
{
	char	*line;

	line = NULL;
    while (get_line(&line) && line && line[0] == '#')
	{
		ft_putendl(line);
		if (ft_strncmp(line, "##", 2) == 0)
			return (NULL);
		free(line);
		line = NULL;
	}
	ft_putendl(line);
	return (line);
}