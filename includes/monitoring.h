/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:58:35 by wjuneo-f          #+#    #+#             */
/*   Updated: 2022/07/31 20:03:33 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITORING_H
# define MONITORING_H

#include <stdio.h>
#include <curl/curl.h>
#include <fcntl.h>
#include ".././libft/libft.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdatomic.h>
#include <signal.h>

typedef struct		s_display_content
{
	char		**http_status;
	char		**http_domain;
	char		**http_date;

	char		**ping_ip;
	char		**ping_domain;
	char		**ping_statistic;

	char		**dns_ip;
	char		**dns_domain;
	char		**dns_date;
	char		**dns_statistic;

}				t_display_content;

typedef struct		s_dns
{
	char		*name;
	char		*protocolo;
	char		*endereco;
	char		*intervalo;
	char		*serv_dns;

	size_t		last_time;

}				t_dns;

typedef struct		s_ping
{
	char		*name;
	char		*protocolo;
	char		*endereco;
	char		*intervalo;

	size_t		last_time;

}					t_ping;

typedef struct		s_http
{
	char		*name;
	char		*protocolo;
	char		*endereco;
	char		*metodo;
	char		*cod;
	char		*intervalo;

	size_t		last_time;

}				t_http;

typedef struct		s_monitoring
{
	t_http				http;
	t_ping				ping;
	t_dns				dns;
	t_display_content	content;

	int					monitoring_db;
	atomic_int			monitoring_log;
	int					save_fd;
	size_t				time_start;
	int					verify_simplify;
}				t_monitoring;

void	init_data(t_monitoring *data);

// Parse
void	parse_monitoring_db(t_monitoring *data);
void	parse_monitoring_http(t_monitoring *data, int fd);
void	parse_monitoring_ping(t_monitoring *data, int fd);
void	parse_monitoring_dns(t_monitoring *data, int fd);

// monitoring
void	ping_monitoring(t_monitoring *data, int *fd);
void	http_monitoring(t_monitoring *data, int fd[]);
void	dns_monitoring(t_monitoring *data, int *fd);

// times
size_t	time_start(void);
size_t	settime(t_monitoring *data);

// utils
int		ft_find_size(char *str);
int		add_str(char **str, char **buffer);


// send
void	send_terminal(t_monitoring *data);
#endif
