/*
** utils.c for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Sun May 14 18:22:50 2017 jurczy_l
** Last update Sun May 21 18:29:00 2017 jurczy_l
*/

#include	"server.h"

int		create_socket(int port)
{
  int		sock;
  struct sockaddr_in	server;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    {
      perror("socket()");
      exit(1);
    }
  bzero((char *) &server, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);
  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
      perror("bind()");
      exit(1);
    }
  listen(sock, 5);
  return (sock);
}

int		connect_data_channel(t_client *client)
{
  struct sockaddr_in	addr;
  struct protoent	*pe;
  int		s;

  pe = getprotobyname("TCP");
  if ((s = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (-1);
  addr.sin_family = AF_INET;
  inet_pton(AF_INET, client->info.ip, &(addr.sin_addr));
  addr.sin_port = htons(client->info.port);
  if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    return (-1);
  client->info.socket = s;
  return (0);
}

int		open_data_channel(t_info *client)
{
  struct sockaddr_in	addr;
  struct protoent	*protoent;
  socklen_t		socket_size;

  protoent = getprotobyname("TCP");
  if ((client->socket = socket(AF_INET, SOCK_STREAM, protoent->p_proto)) == -1)
    return (-1);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(0);
  if (bind(client->socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    return (-1);
  if (listen(client->socket, 5) == -1)
    return (-1);
  socket_size = sizeof(addr);
  if (getsockname(client->socket\
		  , (struct sockaddr *)&addr, &socket_size) == -1)
    return (-1);
  client->port = ntohs(addr.sin_port);
  return (0);
}

int		accept_data_channel(t_client *client)
{
  struct sockaddr_in addr;
  int		a;
  int		new_socket;

  a = sizeof(addr);
  new_socket = accept(client->info.socket,\
		      (struct sockaddr*)&addr, (socklen_t*)&a);
  if (new_socket < 0)
    {
      close_data_channel(client, new_socket);
      return (-1);
    }
  return (new_socket);
}

void            close_data_channel(t_client *client, int socket)
{
  close(client->info.socket);
  if (socket > 0)
    close(socket);
  client->info.mode = NONE;
  client->info.port = -1;
}
