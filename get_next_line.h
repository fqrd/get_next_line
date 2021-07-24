/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaquard <fcaquard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:00:24 by fcaquard          #+#    #+#             */
/*   Updated: 2021/07/24 17:54:55 by fcaquard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char	*buffer;
	char	*rest;
	char	*line;
	int		populated;
	size_t	start;
	size_t	end;
}	t_list;

char	*get_next_line(int fd);
t_list	*new_status(t_list *s);
int		find_char(t_list **s, char c);
char	*substrjoin(t_list **s, size_t start, size_t end, size_t restlen);
void	ft_bzero(void *buff, size_t len);
size_t	ft_strlen(const char *str);

#endif