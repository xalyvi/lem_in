#include "lem_in.h"

int		str_digit(char *line)
{
	if (*line == '0' && *(line + 1) != '\0')
	    return (0);
    while (*line != '\0')
    {
	    if (*line >= '0' && *line <= '9')
            line++;
        else
            return (0);
    }
    return (1);
}

char	*ft_strchr(char *s, int c)
{
    size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return ((size_t)i);
}

char	*ft_strdup(const char *str)
{
	char	*ret;
	int		i;

	i = 0;
	if ((ret = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		ret[ft_strlen(str)] = '\0';
	else
		return (NULL);
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		i = -1;
		j = 0;
		if (!(ret = (char *)malloc(sizeof(char) * len1 + len2 + 1)))
			return (NULL);
		while (++i < len1)
			ret[i] = s1[i];
		while (j < len2)
			ret[i++] = s2[j++];
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}