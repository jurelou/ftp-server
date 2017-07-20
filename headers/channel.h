/*
** channel.h for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Fri May 19 16:44:54 2017 jurczy_l
** Last update Sun May 21 18:01:38 2017 jurczy_l
*/

#ifndef		CHANNEL_H_
# define	CHANNEL_H_

#include        <netdb.h>
#include        <sys/socket.h>
#include        <sys/stat.h>
#include        <fcntl.h>
#include        <netinet/in.h>
#include        <arpa/inet.h>
#include	"constants.h"

typedef enum    e_mode
  {
    NONE,
    PASSIV,
    PORT
  }             t_mode;

typedef struct  s_info
{
  char          *ip;
  int           socket;
  int           port;
  t_mode        mode;
}               t_info;

typedef struct  s_client
{
  t_info        info;
  struct sockaddr_in    addr;
  int           socket;
  char          root_path[ROOT_PATH_LENGTH];
  char          *cmd;
  char          *f_token;
  char          *s_token;
  char          *t_token;
  bool          logged;
  char          *user;
  char          *pass;
}                       t_client;

void            close_data_channel(t_client *client, int socket);
int             accept_data_channel(t_client *client);
int             open_data_channel(t_info *client);
int             create_socket(int port);
int             connect_data_channel(t_client *client);

#endif
