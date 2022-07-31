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

void	http_monitoring(t_monitoring *data)
{
	char	**comand;
	int		status;
	int		pid;


	pid = fork();
	// comand = malloc(sizeof(char) * 4);
	// comand[0] = ft_strdup("curl");
	// comand[1] = ft_strdup("-IX GET");
	// comand[2] = ft_strdup("www.example.com");
	// comand[3] = NULL;
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		//dup2(fd[1], STDOUT_FILENO);
		//close(fd[1]);
		//close(fd[0]);
		execlp("curl", "curl", "-IX GET", "www.facebook.com", NULL);
	}
	waitpid(pid, &status, WNOHANG);
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
