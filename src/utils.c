/*
1;4803;0c** utils.c for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Sun May 14 18:22:50 2017 jurczy_l
** Last update Sun May 21 18:24:01 2017 jurczy_l
*/

#include	"server.h"

void		write_client(int fd, char *str)
{
  write(fd, str, strlen(str));
  write(fd, "\r\n", 2);
}

void		init_client(t_client *data, int sock, \
			    char *root_path, const char *ip)
{
  data->info.ip = strdup(ip);
  data->info.port = -1;
  data->info.socket = -1;
  data->socket = sock;
  bzero(data->root_path, ROOT_PATH_LENGTH);
  strcpy(data->root_path, root_path);
  data->logged = false;
  chdir(root_path);
  data->user = NULL;
  data->pass = NULL;
}

void		exec_ls(t_client *client)
{
  pid_t		pid;

  if ((pid = fork()) == -1)
    perror("Fork()");
  else if (pid == 0)
    {
      dup2(client->info.socket, 1);
      if (client->s_token != NULL)
	{
	  execl("/bin/ls", "ls", "-l", client->s_token, (char *)0);
	}
      else
	execl("/bin/ls", "ls", "-l", (char *)0);
    }
  else
    {
      write_client(client->socket, "226 'ls' correctly send");
      close_data_channel(client, -1);
    }
}

bool		is_valid(char *s, int size)
{
  int		i;

  i = -1;
  if (size <= 2)
    return (false);
  while (s[++i])
    if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\r')
      return (true);
  return (false);
}
