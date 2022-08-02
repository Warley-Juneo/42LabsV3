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

size_t	get_data(char *buffer, size_t itemsize, size_t nitems, void *ignorethis)
{
	size_t	bytes = itemsize * nitems;
	printf("%s\n", buffer);
	return (bytes);
}

void	http_monitoring(t_monitoring *data, int *fd)
{
	char	*comand;
	int		status;
	int		pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		execlp("curl", "curl -s", "-IX GET", "www.facebook.com", NULL);
		// CURL *curl = curl_easy_init();

		// if (!curl)
		// {
		// 	fprintf(stderr, "init failed\n");
		// 	return ;
		// }

		// //set options
		// data->http.endereco = ft_strtrim(data->http.endereco, "\t");
		// curl_easy_setopt(curl, CURLOPT_URL, data->http.endereco);
		// curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_data);

		// // perform out action
		// CURLcode result = curl_easy_perform(curl);
		// if (result != CURLE_OK)
		// {
		// 	fprintf(stderr, "Dowload problem: %s\n", curl_easy_strerror(result));
		// }

		// curl_easy_cleanup(curl);
		// return ;
	}
	waitpid(pid, &status, 0);
}

void	ping_monitoring(t_monitoring *data, int *fd)
{
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
