/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:15:17 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/08/03 00:43:10 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/monitoring.h"

void	init_data(t_monitoring *data, int argc)
{
	data->monitoring_db = open("./config/monitoring.db", O_RDONLY);
	if (data->monitoring_db == -1)
	{
		printf("Monitoring.db não encontrado");
		exit(1);
	}
	data->monitoring_log = open("./logs/monitoring.log", O_RDWR | O_APPEND | O_CREAT, 0777);
	if (data->monitoring_log == -1)
		printf("Meu ovo\n");
	data->http.name = NULL;
	data->http.protocolo = NULL;
	data->http.endereco = NULL;
	data->http.metodo = NULL;
	data->http.cod = NULL;
	data->http.intervalo = NULL;
	data->http.last_time = 0;
	data->ping.name = NULL;
	data->ping.protocolo = NULL;
	data->ping.endereco = NULL;
	data->ping.intervalo = NULL;
	data->ping.last_time = 0;
	data->dns.name = NULL;
	data->dns.protocolo = NULL;
	data->dns.endereco = NULL;
	data->dns.intervalo = NULL;
	data->dns.serv_dns = NULL;
	data->dns.last_time = 0;
}
