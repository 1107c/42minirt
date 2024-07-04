/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:56:29 by myeochoi          #+#    #+#             */
/*   Updated: 2024/03/02 10:15:28 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

static char	*get_arr(char const *s, char c, int *i)
{
	int		j;
	int		k;
	char	*arr;

	while (s[*i] && s[*i] == c)
		(*i)++;
	j = *i;
	while (s[j] && s[j] != c)
		j++;
	arr = (char *)malloc(sizeof(char) * (j + 1));
	if (arr == 0)
		return (0);
	k = 0;
	while (s[*i] && s[*i] != c)
		arr[k++] = s[(*i)++];
	arr[k] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**split_arr;
	int		len;
	int		i;
	int		i_2;

	i = 0;
	i_2 = 0;
	len = word_count(s, c);
	split_arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (split_arr == 0)
		return (0);
	while (i < len)
		split_arr[i++] = get_arr(s, c, &i_2);
	split_arr[i] = 0;
	return (split_arr);
}
/*
#include <stdio.h>
int main()
{
	char s[] = "ohello woroldo";
	char c = 'o';
	char **total;
	int i = 0;
	int l = word_count(s,c);
	total = ft_split(s,c);
	while (i < l)
	{
		printf("%s\n", total[i]);
		i++;
	}
	i = 0;
	while (i < l)
		free (total[i++]);
}*/