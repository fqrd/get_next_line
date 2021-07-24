/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:00:17 by fcaquard          #+#    #+#             */
/*   Updated: 2021/07/22 18:16:35 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*mfree(t_list **s, char *ret)
{
	if (*s)
	{
		if ((*s)->rest != NULL)
			free((*s)->rest);
		if ((*s)->buffer != NULL)
			free((*s)->buffer);
		(*s)->rest = NULL;
		(*s)->buffer = NULL;
		if (*s != NULL)
			free(*s);
		*s = NULL;
	}
	return (ret);
}

static char	*action_on_buffer(t_list **s)
{
	if (find_char(&*s, '\n'))
	{
		(*s)->line = substrjoin(&*s, (*s)->start, (++(*s)->end - (*s)->start),
				ft_strlen((*s)->rest));
		if (!(*s)->line)
			return (mfree(&*s, NULL));
		(*s)->start = (*s)->end;
		return ((*s)->line);
	}
	else
	{
		if ((*s)->start != (*s)->end)
		{
			(*s)->rest = substrjoin(&*s, (*s)->start,
					((*s)->end - (*s)->start), ft_strlen((*s)->rest));
			if (!(*s)->rest)
				return (mfree(&*s, NULL));
		}
		(*s)->populated = 0;
		return ("1");
	}
}

static char	*load_buffer(int fd, t_list **s)
{
	int	res;

	res = read(fd, (*s)->buffer, BUFFER_SIZE);
	if (res > 0)
	{
		(*s)->buffer[res] = '\0';
		(*s)->start = 0;
		(*s)->end = 0;
		(*s)->populated = 1;
		return ("1");
	}
	else if (res == 0 && (*s)->rest != NULL)
	{
		(*s)->line = substrjoin(&*s, 0, 0,
				ft_strlen((*s)->rest));
		if (!(*s)->line)
			return (mfree(&*s, NULL));
		return ((*s)->line);
	}
	return (mfree(s, NULL));
}

char	*get_next_line(int fd)
{
	static t_list	*s[FOPEN_MAX];
	char			*res;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	if (!s[fd])
		s[fd] = new_status(s[fd]);
	while (s[fd])
	{
		s[fd]->line = NULL;
		if (s[fd]->populated)
		{
			res = action_on_buffer(&s[fd]);
			if (res == NULL || s[fd]->line != NULL)
				return (res);
		}
		else
		{
			res = load_buffer(fd, &s[fd]);
			if (res == NULL || s[fd]->line != NULL)
				return (mfree(&s[fd], res));
		}
	}
	return (mfree(&s[fd], NULL));
}
