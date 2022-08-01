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
	char	*buffer = ft_strdup("www.facebook.com");
	char	**comand;
	int		status;
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		//buffer = data->http.endereco;
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execlp("ping", "ping", "-c 1", data->http.endereco, NULL);
	}
	waitpid(pid, &status, WNOHANG);
	data->save_fd = fd[0];
	close(fd[1]);
	while(1)
	{
		buffer = get_next_line(data->save_fd);
		if (buffer == NULL)
			return ;
		printf("%s", buffer);
	}
}

void	ping_monitoring(t_monitoring *data, int *fd)
{
	char	*comand;
	int		status;
	int		pid;

	comand = ft_strjoin("ping -c 1 ", data->ping.endereco);
	system(comand);
}

void	dns_monitoring(t_monitoring *data, int *fd)
{
	char	*comand;
	int		status;
	int		pid;

	comand = ft_strjoin("dig ", data->ping.endereco);
	system(comand);
}
