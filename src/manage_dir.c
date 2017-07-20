/*
** manage_dir.c for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Wed May 10 11:00:58 2017 jurczy_l
** Last update Sun May 21 18:27:18 2017 jurczy_l
*/

#include	"server.h"

void		manage_cwd(t_client *client)
{
  char		buff[256];
  char		cwd[256];

  bzero(buff, 256);
  if (client->logged && client->s_token != NULL)
    {
      if (chdir(client->s_token) != -1)
	{
	  getcwd(cwd, sizeof(cwd));
	  if (!(strncmp(cwd, client->root_path, strlen(client->root_path)) == 0))
	    chdir(client->root_path);
	  write_client(client->socket, "250 Directory successfully changed");
	}
      else
	write_client(client->socket, "550 Failed to change Directory");
    }
  else if (client->logged)
    write_client(client->socket, "550 Failed to change Directory");
  else
    write_client(client->socket, "530 Please login with USER and PASS");
}

void		manage_cdup(t_client *client)
{
  if (client->logged)
    {
      if (chdir(client->root_path) != -1)
	write_client(client->socket, "250 Directory successfully changed");
      else
	write_client(client->socket, "550 Failed to change Directory");
    }
  else
    write_client(client->socket, "530 Please login with USER and PASS");
}

void		manage_pwd(t_client *client)
{
  char		cwd[1024];

  if (client->logged)
    {
      if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
	  write(client->socket, "257 \"", 5);
	  if (strlen(cwd) == strlen(client->root_path))
	    write(client->socket, "/", 1);
	  else
	    write(client->socket, cwd + strlen(client->root_path)\
		  , strlen(cwd) - strlen(client->root_path));
	  write_client(client->socket, "\"");
	}
      else
	perror("getcwd() error");
    }
  else
    write_client(client->socket, "530 Please login with USER and PASS");
}

static void		exec_passiv_ls(t_client *client)
{
  int		tmp_sock;
  pid_t		pid;

  if ((tmp_sock = accept_data_channel(client)) == -1)
    write_client(client->socket, "520 LIST impossible to reach client\n");
  else
    {
      write_client(client->socket, "150 Here comes the directory listing");
      if ((pid = fork()) == -1)
	perror("Fork()");
      else if (pid == 0)
	{
	  dup2(tmp_sock, 1);
	  execl("/bin/ls", "ls", "-l", client->s_token, (char *)0);
	}
      else
	{
	  write_client(client->socket, "226 'ls' correctly send");
	  close_data_channel(client, tmp_sock);
	}
    }
}

void		manage_list(t_client *client)
{
  if (client->info.mode == PASSIV)
    exec_passiv_ls(client);
  else if (client->info.mode == PORT)
    {
      write_client(client->socket,					\
		   "150 Opening BINARY mode data connection for 'ls'");
      if (connect_data_channel(client) == -1)
	write_client(client->socket, "520 Impossible to reach client");
      else
	exec_ls(client);
    }
  else
    write_client(client->socket, "425 Use PORT or PASV first");
}
