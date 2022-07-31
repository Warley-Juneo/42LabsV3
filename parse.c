/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:16:00 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/07/29 17:17:06 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/monitoring.h"

int	validate_parse_http(t_monitoring *data)
{
	int	i;

	i = 0;
	if (!ft_strcmp(data->http.protocolo, "HTTP"))
	{
		write(2, "Config protocolo http Error\n", 32);
		exit(1);
	}
	else if (!ft_strcmp(data->http.metodo, "GET") || !ft_strcmp(data->http.metodo, "POST"))
	{
		write(2, "Config metodo Error\n", 22);
		exit(1);
	}
	data->http.cod = ft_strtrim(data->http.cod, "\t");
	while (data->http.cod[i])
	{
		if (!ft_isdigit(data->http.cod[i]))
		{
			write(2, "Config codigo http Error\n", 27);
			exit(1);
		}
		i++;
	}
	i = 0;
	while (data->http.intervalo[i])
	{
		if (!ft_isdigit(data->http.intervalo[i]))
		{
			write(2, "Config interval http Error\n", 28);
			exit(1);
		}
		i++;
	}
}

void	parse_monitoring_http(t_monitoring *data, int fd)
{
	char	*buffer;
	int		size;

	buffer = get_next_line(fd);
	buffer = ft_strtrim(buffer, "\n");
	add_str(&data->http.name, &buffer);
	add_str(&data->http.protocolo, &buffer);
	add_str(&data->http.endereco, &buffer);
	add_str(&data->http.metodo, &buffer);
	add_str(&data->http.cod, &buffer);
	add_str(&data->http.intervalo, &buffer);
	validate_parse_http(data);
}

int	validate_parse_ping(t_monitoring *data)
{
	int	i;

	i = 0;
	if (!ft_strcmp(data->http.protocolo, "PING"))
	{
		write(2, "Config protocolo ping Error\n", 30);
		exit (1);
	}
	while (data->ping.intervalo[i])
	{
		if (!ft_isdigit(data->ping.intervalo[i]))
		{
			write(2, "Config interval ping Error\n", 29);
			exit (1);
		}
		i++;
	}
}

void	parse_monitoring_ping(t_monitoring *data, int fd)
{
	char	*buffer;
	int		size;

	buffer = get_next_line(fd);
	buffer = ft_strtrim(buffer, "\n");
	add_str(&data->ping.name, &buffer);
	add_str(&data->ping.protocolo, &buffer);
	add_str(&data->ping.endereco, &buffer);
	add_str(&data->ping.intervalo, &buffer);
	validate_parse_ping(data);
}

int	validate_parse_dns(t_monitoring *data)
{
	int	i;

	i = 0;
	if (!ft_strcmp(data->http.protocolo, "DNS"))
	{
		write(2, "Config protocolo dns Error\n", 29);
		exit (1);
	}
	while (data->dns.intervalo[i])
	{
		if (!ft_isdigit(data->dns.intervalo[i]))
		{
			write(2, "Config interval dns Error\n", 29);
			exit (1);
		}
		i++;
	}
}

void	parse_monitoring_dns(t_monitoring *data, int fd)
{
	char	*buffer;
	int		size;

	buffer = get_next_line(fd);
	buffer = ft_strtrim(buffer, "\n");
	add_str(&data->dns.name, &buffer);
	add_str(&data->dns.protocolo, &buffer);
	add_str(&data->dns.endereco, &buffer);
	add_str(&data->dns.intervalo, &buffer);
	validate_parse_dns(data);
}

