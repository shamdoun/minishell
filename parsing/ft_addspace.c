#include "../minishell.h"

int	ft_cmdlenght(char *s)
{
	int		len;
	int		i;
	char	o;

	(1) && (len = 0, i = 0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			o = s[i++];
			len++;
			while (s[i] != o)
				(1) && (len++, i++);
		}
		if (s[i] == '<' || s[i] == '>')
		{
			o = s[i];
			if (i > 0 && s[i - 1] != o && s[i - 1] != ' ' && s[i - 1] != '\t')
				len++;
			if (s[i + 1] != o && s[i + i] != ' ' && s[i + 1] != '\t')
				len++;
		}
		(1) && (i++, len++);
	}
	return (len);
}

char	*putstring(char *s, t_space *v)
{
	while (s[v->i])
	{
		if (s[v->i] == '\'' || s[v->i] == '"')
		{
			(1) && (v->o = s[v->i], v->ptr[v->j++] = s[v->i++]);
			while (s[v->i] != v->o)
				v->ptr[v->j++] = s[v->i++];
		}
		if (v->i > 0 && ((s[v->i] == '>' && s[v->i - 1] != '>')
				|| (s[v->i] == '<' && s[v->i - 1] != '<')))
		{
			if (v->i > 0 && (s[v->i - 1] != ' ' && s[v->i - 1] != '\t'))
				(1) && (v->ptr[v->j] = ' ', v->ptr[++v->j] = s[v->i], v->slen = 1);
		}
		if (s[v->i + 1] && ((s[v->i] == '>' && s[v->i + 1] != '>')
				|| (s[v->i] == '<' && s[v->i + 1] != '<')))
		{
			if (s[v->i + 1] != ' ' && s[v->i + 1] != '\t')
				(1) && (v->ptr[v->j] = s[v->i], v->ptr[++v->j] = ' ', v->slen = 1);
		}
		if (v->slen == 0)
			v->ptr[v->j] = s[v->i];
		(1) && (v->slen = 0, v->j++, v->i++);
	}
	return (v->ptr[v->j] = '\0', v->ptr);
}

char	*ft_strwithspace(char *s)
{
	t_space	v;

	(1) && (v.i = 0, v.j = 0, v.slen = ft_cmdlenght(s));
	v.ptr = malloc(v.slen + 1);
	v.slen = 0;
	putstring(s, &v);
	return (v.ptr);
}

// void	add_space(t_commands *cmd)
// {
// 	while (cmd)
// 	{

// 	}
// }
