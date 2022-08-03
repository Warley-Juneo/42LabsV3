/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:45:57 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/08/02 23:06:14 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/monitoring.h"


void	http_monitoring(t_monitoring *data, int *fd)
{
	CURL	*curl;
	CURLcode res;

	curl = curl_easy_init();
	data->http.endereco = ft_strtrim(data->http.endereco, "\t");
  	if(curl) 
	{
    	curl_easy_setopt(curl, CURLOPT_URL, data->http.endereco);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1l);
   		res = curl_easy_perform(curl);
		data->http.t = time(NULL);
		data->http.time = localtime(&data->http.t);
		if(res != CURLE_OK)
      		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &data->http.code);
   		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
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
