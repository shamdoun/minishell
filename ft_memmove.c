#include "minishell.h"

void	*ft_memmove(void *dst, const void *src, size_t len )
{
	char	*d;
	char	*s;
	int		i;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (dst == src || len == 0)
		return (dst);
	if (d > s)
	{
		while (len)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
