/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:20:53 by yeojukim          #+#    #+#             */
/*   Updated: 2024/03/20 13:20:54 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (0);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (ft_strlen(s) < start)
		len = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

static char	*buf_read(int fd, char *buf, char *snap)
{
	char	*ret;
	int		rlen;

	rlen = read(fd, buf, BUFFER_SIZE);
	while (rlen)
	{
		if (rlen == -1)
			return (NULL);
		buf[rlen] = '\0';
		if (!snap)
			snap = ft_strjoin("", "");
		ret = snap;
		snap = ft_strjoin(ret, buf);
		free (ret);
		ret = NULL;
		if (!snap)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
		rlen = read(fd, buf, BUFFER_SIZE);
	}
	return (snap);
}

static char	*buf_save(char *ret)
{
	size_t	l;
	int		i;
	char	*buf;

	i = 0;
	while (ret[i] && ret[i] != '\n')
		i++;
	if (!ret[i++])
		return (NULL);
	l = ft_strlen(ret);
	buf = ft_substr(ret, i, l - (i - 1));
	if (!buf)
		return (NULL);
	if (!*buf)
	{
		free (buf);
		buf = NULL;
		return (NULL);
	}
	ret[i] = '\0';
	return (buf);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	char		*ret;
	static char	*snap;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	ret = buf_read(fd, buf, snap);
	free (buf);
	buf = NULL;
	if (!ret)
		return (0);
	snap = buf_save(ret);
	*line = ret;
	if (!ret)
		return (0);
	return (1);
}
