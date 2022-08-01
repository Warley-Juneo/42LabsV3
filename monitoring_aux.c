/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:45:57 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/07/31 20:36:38 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/monitoring.h"

void	http_monitoring(t_monitoring *data, int fd[])
{
	char	*buffer;
	char	**comand;
	int		status;
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		data->http.endereco = ft_strtrim(data->http.endereco, "\t");
		dup2(fd[1], STDOUT_FILENO);
		execlp("curl", "curl", "-s", "-IX GET", data->http.endereco, NULL);
	}
	waitpid(pid, &status, 0);
}

void	ping_monitoring(t_monitoring *data, int *fd)
{
	char	*buffer;
	char	**comand;
	int		status;
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		data->ping.endereco = ft_strtrim(data->ping.endereco, "\t");
		dup2(fd[1], STDOUT_FILENO);
		execlp("ping", "ping", "-c 1", data->ping.endereco, NULL);
	}
	waitpid(pid, &status, 0);
}

void	dns_monitoring(t_monitoring *data, int *fd)
{
	char	*buffer;
	char	**comand;
	int		status;
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		data->dns.endereco = ft_strtrim(data->dns.endereco, "\t");
		dup2(fd[1], STDOUT_FILENO);
		execlp("dig", "dig", data->dns.endereco, NULL);
	}
	waitpid(pid, &status, 0);
}
