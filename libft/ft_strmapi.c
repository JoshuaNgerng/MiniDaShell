/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mukhairu <mukhairu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:57:03 by mukhairu          #+#    #+#             */
/*   Updated: 2022/10/11 14:53:37 by mukhairu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Return: The string created from successive applications of 'f'. NULL if fails.
Applies function 'f' to each character of the string 's', 
and passing it's index as first argument to create a new string (with malloc)
resulting from successive applications of 'f' 
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*char f(unsigned int i, char c)
{
	char str;
	str = c + 1;
	return (str);
}

int main(void)
{
	char str1[] = "WOW!";
	char *str2;

	str2 = ft_strmapi(str1, *f);
	printf("%s\n",str2);
	return (0);
}*/
