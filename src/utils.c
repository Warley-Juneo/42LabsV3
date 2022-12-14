/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:16:53 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/08/03 00:04:30 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/monitoring.h"

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
	if (temp[size - 1])
		*buffer = ft_strdup(temp + size);
	return (0);
}
