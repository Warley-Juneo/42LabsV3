/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:58:35 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/08/03 00:40:52 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/monitoring.h"

int		c_sig = 0;

void sigint(int sig)
{
	c_sig = 1;
}

int	main(int argc, char *argv[])
{
	t_monitoring	data;


	if (argc > 2)
	{
		printf("Too many arguments\n");
		exit(1);
	}
	data.verify_simplify = 0;
	if (argc == 2)
	{
		if (!ft_strncmp(argv[1], "--simplify", ft_strlen(argv[1])))
			data.verify_simplify = 1;
		else if (!ft_strncmp(argv[1], "--help", ft_strlen(argv[1])))
		{
			char	*buffer;
			int		man;

			man = open("manual.txt", O_RDONLY);
			while (1)
			{
				buffer = get_next_line(man);
				if (!buffer)
					break ;
				printf("%s", buffer);
			}
			exit(1);
		}
		else
		{
			printf("Invalid argument -> Use --symplify\n");
			exit(1);
		}
	}
	signal(SIGINT, sigint);
	init_data(&data, argc);
	parse_monitoring_db(&data);
	data.time_start = time_start();
	start_monitoring(&data);
	exit(1);
	return (0);
}

void	parse_monitoring_db(t_monitoring *data)
{
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
		if (settime(data) - data->http.last_time == 0 || settime(data) - data->http.last_time >= (size_t)ft_atoi(data->http.intervalo))
		{
			data->http.last_time = settime(data);
			http_monitoring(data, fd);
			if (data->verify_simplify)
				send_terminal_http_s(data);
			else
				send_terminal_http(data);
		}
		if (settime(data) - data->ping.last_time == 0 || settime(data) - data->ping.last_time >= (size_t)ft_atoi(data->ping.intervalo))
		{
			data->ping.last_time = settime(data);
			ping_monitoring(data, fd);
		}
		if (settime(data) - data->dns.last_time == 0 || settime(data) - data->dns.last_time >= (size_t)ft_atoi(data->dns.intervalo))
		{
			data->dns.last_time = settime(data);
			dns_monitoring(data, fd);
		}
		data->save_fd = fd[0];
		close(fd[1]);
		send_terminal(data);
		close(fd[0]);
		sleep(1);
	}
}

