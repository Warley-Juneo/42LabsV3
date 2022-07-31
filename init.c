/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:15:17 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/07/31 18:19:56 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/monitoring.h"

void	init_data(t_monitoring *data)
{
	data->verify_simplify = 0;
	data->monitoring_db = open("./config/monitoring.db", O_RDONLY, O_APPEND);
	data->monitoring_log = open("./logs/monitoring.log", O_RDWR);
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

	data->content.http_status = NULL;
	data->content.http_date = NULL;
	data->content.http_domain = NULL;

	data->content.ping_ip = NULL;
	data->content.ping_domain = NULL;
	data->content.ping_statistic = NULL;

	data->content.dns_ip = NULL;
	data->content.dns_domain = NULL;
	data->content.dns_date = NULL;
	data->content.dns_statistic = NULL;
}
