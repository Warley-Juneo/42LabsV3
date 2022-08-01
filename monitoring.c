/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:58:35 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/07/31 19:05:23 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/monitoring.h"

int c_sig = 0;

static	void sigint(int sig)
{
	(void)sig;
	c_sig = 1;
}

void	start_monitoring(t_monitoring *data);

int	main(int argc, char *argv[])
{
	t_monitoring	data;

	if (argc > 2)
		printf("Too many arguments\n");
	if (argc == 2)
	{
		if (ft_strcmp(argv[1], "--symplify"))
			data.verify_simplify = 1;
		else
			printf("Invalid argument -> Use --symplify\n");
	}
	signal(SIGINT, sigint);
	init_data(&data);
	parse_monitoring_db(&data);
	data.time_start = time_start();
	start_monitoring(&data);
	return (0);
}

void	parse_monitoring_db(t_monitoring *data)
{
	if (data->monitoring_db == -1)
	{
		printf("Invalid file\n");
		close(data->monitoring_db);
		exit(1);
	}
	parse_monitoring_http(data, data->monitoring_db);
	parse_monitoring_ping(data, data->monitoring_db);
	parse_monitoring_dns(data, data->monitoring_db);
}

void	start_monitoring(t_monitoring *data)
{
	char	*buffer;
	int		temp_out;
	int		fd[2];

	temp_out = dup(1);
	while (!c_sig)
	{
		if (pipe(fd) == -1)
			return ;
		// if (settime(data) - data->http.last_time == 0 || settime(data) - data->http.last_time >= (size_t)ft_atoi(data->http.intervalo))
		// {
		// 	data->http.last_time = settime(data);
		// 	http_monitoring(data, fd);
		// }
		if (settime(data) - data->ping.last_time == 0 || settime(data) - data->ping.last_time >= (size_t)ft_atoi(data->ping.intervalo))
		{
			data->ping.last_time = settime(data);
			ping_monitoring(data, fd);
		}
		data->save_fd = fd[0];
		if (settime(data) - data->dns.last_time == 0 || settime(data) - data->dns.last_time >= (size_t)ft_atoi(data->dns.intervalo))
		{
			data->dns.last_time = settime(data);
			dns_monitoring(data, fd);
		}
		close(fd[1]);
		send_terminal(data);
		close(fd[0]);
		sleep(1);
	}
}

void	send_terminal(t_monitoring *data)
{
	char	*buffer;
	char	**content;
	char	*temp;
	int		x, y, z, nb = 0;

	while (1)
	{
		buffer = get_next_line(data->save_fd);
		if (buffer == NULL)
			break ;

		//Info HTTP
		// if (strstr(buffer, "HTTP/2"))
		// {
		// 	content = ft_split(buffer, ' ');
		// 	data->content.http_status[x] = content[1];
		// 	fprintf(stderr, "%s\n", data->content.http_status[x]);
		// }
		// else if (strstr(buffer ,"domain=."))
		// {
		// 	temp = ft_strchr(buffer, '.');
		// 	data->content.http_domain[x] = temp + 1;
		// 	fprintf(stderr, "%s\n", data->content.http_domain[x]);
		// }
		// else if (strstr(buffer, "date:"))
		// {
		// 	data->content.http_date[x] = ft_strchr(buffer, 'S');
		// 	fprintf(stderr, "%s\n", data->content.http_date[x]);
		// 	x++;
		// }

		// Info PING
		else if (strstr(buffer, "PING"))
		{
			content = ft_split(buffer, ' ');
			while (content[y])
			{
				printf("Content = %s\n", content[y++]);
			}
			data->content.ping_domain[y] = content[1];
			data->content.ping_ip[y] = content[2];
			fprintf(stderr, "%s\n", data->content.ping_domain[y]);
			fprintf(stderr, "%s\n", data->content.ping_ip[y]);
		}
		else if (strstr(buffer, "transmitted"))
		{
			data->content.ping_statistic[y] = buffer;
			fprintf(stderr, "%s\n", data->content.ping_statistic[y]);
			y++;
		}

		// Info DNS
		else if (strstr(buffer, "QUERY: "))
		{
			temp = ft_strchr(buffer, 'Q');
			data->content.dns_statistic[z] = temp;
			fprintf(stderr, "%s\n", data->content.dns_statistic[z]);
		}
		else if (strstr(buffer, "ANSWER: SECTION:"))
		{
			free(buffer);
			buffer = get_next_line(data->save_fd);
			content = ft_split(buffer, '\t');
			data->content.dns_domain[z] = ft_strtrim(buffer, ".");
			data->content.dns_ip[z] = content[5];
			fprintf(stderr, "%s\n", data->content.dns_domain[z]);
			fprintf(stderr, "%s\n", data->content.dns_ip[z]);
		}
		else if (strstr(buffer, "WHEN: "))
		{
			temp = ft_strchr(buffer, 'S');
			data->content.dns_date[z] = temp;
			z++;
		}
	}

	// printf("%s\n",data->content.http_status[0]);
	// printf("%s\n",data->content.http_domain[0]);
	// printf("%s\n",data->content.http_date[0]);

	// printf("%s\n",data->content.ping_domain[0]);
	// printf("%s\n",data->content.ping_ip[0]);
	// printf("%s\n",data->content.ping_statistic[0]);

	// printf("%s\n",data->content.dns_statistic[0]);
	// printf("%s\n",data->content.dns_domain[0]);
	// printf("%s\n",data->content.dns_ip[0]);
	// printf("%s\n",data->content.dns_date[0]);

}
