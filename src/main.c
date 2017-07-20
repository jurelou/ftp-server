/*
** main.c for Project-Master in /home/louis/Documents/PSU_2016_myftp/src
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Sun May 21 18:02:25 2017 jurczy_l
** Last update Sun May 21 20:56:10 2017 jurczy_l
*/

#include	"server.h"

static int	exec_client(t_client *data)
{
  t_parser	*tmp;

  tmp = init();
  while (tmp)
    {
      if (strcmp(data->f_token, tmp->cmd) == 0)
  	{
  	  if (strcmp(data->f_token, "QUIT") == 0)
  	    {
  	      write_client(data->socket, "221 Ciao ciao BB");
	      if (data->socket)
		close(data->socket);
	      if (data->info.socket)
		close(data->info.socket);
  	      return (-1);
  	    }
  	  tmp->ptr(data);
  	  return (0);
  	}
      tmp = tmp->next;
    }
  write_client(data->socket, "500 Unknown command");
  return (0);
}

static void	client_loop(int sock, t_client *data)
{
  char		*buffer;
  ssize_t	n_read;
  size_t	len;
  FILE		*fd;

  buffer = NULL;
  fd = fdopen(sock, "r+");
  len = 0;
  while ((n_read = getline(&buffer, &len, fd)) != -1)
    {
      if (is_valid(buffer, len) == false)
	write_client(data->socket, "500 Unknown command");
      else if (buffer[n_read - 1] == 10 && buffer[n_read - 2] == 13)
	{
	  buffer[n_read - 1] = '\0';
	  buffer[n_read - 2] = '\0';
	  data->cmd = strdup(buffer);
	  data->f_token = strtok(buffer, " ");
	  data->s_token = strtok(NULL, " ");
	  data->t_token = strtok(NULL, " ");
	  if (exec_client(data) == -1)
	    return ;
	}
    }
}

static void	server_loop(int sock, char *root_path, const char *ip)
{
  pid_t		pid;
  t_client	data;

  if ((pid = fork()) == -1)
    {
      close(sock);
      exit(1);
    }
  else if (pid > 0)
    {
      close(sock);
    }
  else if (pid == 0)
    {
      init_client(&data, sock, root_path, ip);
      client_loop(sock, &data);
      close(sock);
      exit(0);
    }
}

static void		main_loop(int socket, char *root_path)
{
  int			client;
  socklen_t		size;
  struct sockaddr_in	cli_addr;
  char			buf[INET_ADDRSTRLEN];

  size = sizeof(cli_addr);
  bzero(buf, INET_ADDRSTRLEN);
  while ((client = accept(socket, (struct sockaddr *)&cli_addr, &size)))
    {
      inet_ntop(AF_INET, &cli_addr.sin_addr, buf, sizeof buf);
      write_client(client, "220 Welcome!");
      if (client < 0)
	return;
      server_loop(client, root_path, buf);
    }
}

int			main(int ac, char **av)
{
  int		socket;
  struct stat	file_stat;

  if (ac != 3)
    {
      printf("Usage : ./server <IP> <HOME_DIRECTORY>");
      return (2);
    }
  if (stat(av[2], &file_stat) != 0 || (!(S_ISDIR(file_stat.st_mode))))
    {
      printf("Second argument is not a valid directory.");
      return (1);
    }
  socket = create_socket(atoi(av[1]));
  signal(SIGINT, interupt_handler);
  main_loop(socket, av[2]);
  close(socket);
  return (0);
}
