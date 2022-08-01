/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:16:53 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/07/28 17:54:34 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/monitoring.h"

int	ft_find_size(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[j] == ' ' && str[j] != '\t')
		j++;
	while (str[j])
	{
		i++;
		j++;
		if (str[j] == '\t')
			break;

	}
	return (i + 1);
}

int	add_str(char **str, char **buffer)
{
	int		size;
	char	*temp;

	temp = *buffer;
	size = ft_find_size(*buffer);
	*str = ft_substr(*buffer, 0, size);
	*str = ft_strtrim(*str, "\t");
	*buffer = ft_strdup(temp + size);
	free(temp);
	return (0);
}
