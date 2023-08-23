/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:07:18 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/18 13:31:09 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Return: The array of new strings resulting from the split. NULL if fails
 Allocates (with malloc) and returns an array of strings obtained 
 splitting 's' using the character 'c' as a delimiter. The array must end
 with NULL pointer.
*/

static size_t	ft_countwords(const char *str, char c)
{
	int	i;
	int	count;
	int	detect;

	i = 0;
	count = 0;
	detect = 0;
	while (str[i])
	{
		if (str[i] != c && detect == 0)
		{
			detect = 1;
			count++;
		}
		else if (str[i] == c)
			detect = 0;
		i++;
	}
	return (count);
}

static int	ft_count(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	count;
	char	**str;

	i = 0;
	count = 0;
	if (!s)
		return (NULL);
	str = (char **)ft_calloc((ft_countwords(s, c) + 1), sizeof(char *));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			j = ft_count(&s[i], c);
			str[count++] = ft_substr(s, i, j);
			i = i + j - 1;
		}
		i++;
	}
	return (str);
}

// int	main(void)
// {
//     int		index;
//     char	**split;

//     char c = '-';
//     split = ft_split("--1-2--3---4----5-----42", c);
//     index = 0;
//     while (index < ft_countwords("--1-2--3---4----5-----42", c))
//     {
// 		printf("%d) ", index);
//         printf("%s\n", split[index]);
//         index++;
//     }

// 	while (index >= 0)
// 	{
// 		free(split[index]);
// 		index--;
// 	}
// }
