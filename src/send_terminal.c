/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:45:49 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/08/02 16:45:49 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/monitoring.h"

void	send_terminal(t_monitoring *data)
{
	char	*buffer;
	char	*temp;

	while (1)
	{
		buffer = get_next_line(data->save_fd);
		if (buffer == NULL)
			break ;
        if (strstr(buffer, "PING"))
		{
            if (data->verify_simplify)
			    send_terminal_ping_s(data, buffer);
            else
                send_terminal_ping(data, buffer);
        }
		else if (strstr(buffer, "status: "))
		{
            if (data->verify_simplify)
			    send_terminal_dns_s(data, buffer);
            else
                send_terminal_dns(data, buffer);
        }
	}
}

void	send_terminal_http_s(t_monitoring *data)
{
	char	**content;

	// printf("\033[1;34m|----------------------------------HTTP----------------------------------|\033[1;37m\n");
	// dprintf(data->monitoring_log, "|----------------------------------HTTP----------------------------------|\n");
	// printf("\033[1;34m|\033[0;32mNome:\033[1;37m %s\n", data->http.name);
	// dprintf(data->monitoring_log, "|Nome: %s\n", data->http.name);
	// printf("\033[1;34m|\033[0;32mStatus:\033[1;37m %d\n", data->http.code);
	// dprintf(data->monitoring_log, "|Status: %d", data->http.code);
	// get_next_line(data->save_fd);
	// buffer = ft_strchr(get_next_line(data->save_fd), ':');
	// printf("\033[1;34m|\033[0;32mDate:\033[1;37m %s", buffer + 2);
	// dprintf(data->monitoring_log, "|Date: %s", buffer + 2);
	// printf("\033[1;34m|------------------------------------------------------------------------|\033[1;37m\n");
	// dprintf(data->monitoring_log, "|------------------------------------------------------------------------|\n");

	return ;
}

void	send_terminal_ping_s(t_monitoring *data, char *buffer)
{
	char	**content;

	printf("\033[1;34m|----------------------------------PING----------------------------------|\n");
	dprintf(data->monitoring_log,"|----------------------------------PING----------------------------------|\n");
	content = ft_split(buffer, ' ');
	printf("\033[1;34m|\033[0;32mNome:\033[1;37m %s\n", data->ping.name);
	dprintf(data->monitoring_log, "|Nome: %s\n", data->ping.name);
	printf("\033[1;34m|\033[0;32mEndereço:\033[1;37m %s\n", content[1]);
	dprintf(data->monitoring_log, "|Endereço: %s\n", content[1]);
	printf("\033[1;34m|\033[0;32mIP:\033[1;37m %s\n", content[2]);
	dprintf(data->monitoring_log, "|IP: %s\n", content[2]);
	get_next_line(data->save_fd);
	get_next_line(data->save_fd);
	get_next_line(data->save_fd);
	printf("\033[1;34m|\033[0;32mStatistics:\033[1;37m %s", get_next_line(data->save_fd));
	dprintf(data->monitoring_log, "|Statistics: %s", get_next_line(data->save_fd));
	printf("\033[1;34m|------------------------------------------------------------------------|\033[1;37m\n");
	dprintf(data->monitoring_log,"|------------------------------------------------------------------------|\n");
}

void	send_terminal_dns_s(t_monitoring *data, char *buffer)
{
	char	**content;
	char	*temp;
	int	i;

	i = 0;
	printf("\033[1;34m|----------------------------------DNS-----------------------------------|\033[1;37m\n");
	dprintf(data->monitoring_log, "|----------------------------------DNS-----------------------------------|\n");
	printf("\033[1;34m|\033[0;32mNome:\033[1;37m %s\n", data->dns.name);
	dprintf(data->monitoring_log, "|Nome: %s\n", data->dns.name);
	printf("\033[1;34m|\033[1;32mStatus:\033[1;37m %s", ft_strchr(buffer, 's'));
	dprintf(data->monitoring_log, "|Status: %s", ft_strchr(buffer, 's'));
	temp = ft_strchr(get_next_line(data->save_fd), 'Q');
	printf("\033[1;34m|\033[0;32mStatistics:\033[1;37m %s", temp);
	dprintf(data->monitoring_log, "|Statistics: %s", temp);
	while (i++ < 6)
		get_next_line(data->save_fd);
	free(buffer);
	buffer = get_next_line(data->save_fd);
	content = ft_split(buffer, '\t');
	printf("\033[1;34m|\033[0;32mEndereço / ip:\033[1;37m %s / %s", ft_strtrim(content[0], "."), content[4]);
	dprintf(data->monitoring_log, "|Endereço / ip: %s / %s", ft_strtrim(content[0], "."), content[4]);
	get_next_line(data->save_fd);
	get_next_line(data->save_fd);
	get_next_line(data->save_fd);
	free(buffer);
	buffer = ft_strchr(get_next_line(data->save_fd), ':');
	printf("\033[1;34m|\033[0;32mDate:\033[1;37m %s", buffer + 2);
	dprintf(data->monitoring_log, "|Date: %s", buffer + 2);
	printf("\033[1;34m|------------------------------------------------------------------------|\033[1;37m\n");
	dprintf(data->monitoring_log, "|------------------------------------------------------------------------|\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void	send_terminal_http(t_monitoring *data)
{
	char	**content;

	printf("\033[1;34m|----------------------------------HTTP----------------------------------|\033[1;37m\n");
	printf("\033[1;34m|\033[0;32mNome:\033[1;37m %s\n", data->http.name);
	printf("\033[1;34m|\033[0;32mEndereço:\033[1;37m %s\n", data->http.endereco);
	printf("\033[1;34m|\033[0;32mStatus:\033[1;37m %d\n", data->http.code);
	printf("\033[1;34m|\033[0;32mSaúde:\033[1;37m %s\n", (data->http.code != 200) ? "ko" : "ok");
	dprintf(data->monitoring_log, "%s\n", data->http.name);
    dprintf(data->monitoring_log, "%d\n", data->http.code);
	printf("\033[1;34m|\033[0;32mDate:\033[1;37m %s", asctime(data->http.time));
	dprintf(data->monitoring_log,  "%s\n", asctime(data->http.time));
	printf("\033[1;34m|------------------------------------------------------------------------|\033[1;37m\n");
}

void	send_terminal_ping(t_monitoring *data, char *buffer)
{
	char	**content;

	printf("\033[1;34m|----------------------------------PING----------------------------------|\n");
	content = ft_split(buffer, ' ');
	printf("\033[1;34m|\033[0;32mNome:\033[1;37m %s\n", data->ping.name);
	printf("\033[1;34m|\033[0;32mEndereço:\033[1;37m %s\n", content[1]);
	printf("\033[1;34m|\033[0;32mIP:\033[1;37m %s\n", content[2]);
    dprintf(data->monitoring_log, "%s", buffer);
	dprintf(data->monitoring_log, "%s", get_next_line(data->save_fd));
	dprintf(data->monitoring_log, "%s", get_next_line(data->save_fd));
	dprintf(data->monitoring_log, "%s", get_next_line(data->save_fd));
    free(buffer);
    buffer = get_next_line(data->save_fd);
	printf("\033[1;34m|\033[0;32mStatistics:\033[1;37m %s", buffer);
    dprintf(data->monitoring_log, "%s", buffer);
	printf("\033[1;34m|------------------------------------------------------------------------|\033[1;37m\n");
    free(buffer);
}

void	send_terminal_dns(t_monitoring *data, char *buffer)
{
	char	**content;
	char	*temp;
	int	i;

	i = 0;
	printf("\033[1;34m|----------------------------------DNS-----------------------------------|\033[1;37m\n");
	printf("\033[1;34m|\033[0;32mNome:\033[1;37m %s\n", data->dns.name);
    dprintf(data->monitoring_log, "%s\n", data->dns.name);
	printf("\033[1;34m|\033[1;32mStatus:\033[1;37m %s", ft_strchr(buffer, 's'));
    dprintf(data->monitoring_log, "%s", buffer);
    free(buffer);
    buffer = get_next_line(data->save_fd);
	temp = ft_strchr(buffer, 'Q');
	printf("\033[1;34m|\033[0;32mStatistics:\033[1;37m %s", temp);
	while (i++ < 6)
		dprintf(data->monitoring_log, "%s", get_next_line(data->save_fd));
	free(buffer);
	buffer = get_next_line(data->save_fd);
	content = ft_split(buffer, '\t');
	printf("\033[1;34m|\033[0;32mEndereço / ip:\033[1;37m %s / %s", ft_strtrim(content[0], "."), content[4]);
	dprintf(data->monitoring_log, "%s", get_next_line(data->save_fd));
	dprintf(data->monitoring_log, "%s", get_next_line(data->save_fd));
	dprintf(data->monitoring_log, "%s", get_next_line(data->save_fd));
	free(buffer);
    buffer = get_next_line(data->save_fd);
	buffer = ft_strchr(buffer, ':');
	printf("\033[1;34m|\033[0;32mDate:\033[1;37m %s", buffer + 2);
	printf("\033[1;34m|------------------------------------------------------------------------|\033[1;37m\n");
}