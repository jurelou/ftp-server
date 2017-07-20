/*
** server.h for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Wed May 10 09:55:51 2017 jurczy_l
** Last update Sun May 21 18:23:48 2017 jurczy_l
*/

#ifndef		SERVER_H_
# define	SERVER_H_

#include	<stdbool.h>
#include        <stdlib.h>
#include	<string.h>
#include	<signal.h>
#include        <unistd.h>
#include        <stdio.h>
#include	"channel.h"

typedef void (*cmd_ptr)(t_client *client);
typedef struct		s_parser
{
  char			*cmd;
  cmd_ptr		ptr;
  struct s_parser	*next;
}			t_parser;

void		init_client(t_client *data, int sock,		\
			    char *root_path, const char *ip);
void		interupt_handler();
void		write_client(int fd, char *str);
void		manage_user(t_client *client);
void		manage_pass(t_client *client);
void		manage_cwd(t_client *client);
void		manage_cdup(t_client *client);
void		manage_quit(t_client *client);
void		manage_delete(t_client *client);
void		manage_pwd(t_client *client);
void		manage_pasv(t_client *client);
void		manage_port(t_client *client);
void		manage_help(t_client *client);
void		manage_noop(t_client *client);
void		manage_retr(t_client *client);
void		manage_stor(t_client *client);
void		manage_list(t_client *client);
bool		is_valid(char *s, int size);
t_parser	*init();
void		exec_ls(t_client *);

#endif
