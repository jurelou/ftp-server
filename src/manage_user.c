/*
** manage_user.c for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Wed May 10 10:58:10 2017 jurczy_l
** Last update Sun May 21 18:28:00 2017 jurczy_l
*/

#include	"server.h"

void		manage_user(t_client *client)
{
  if (client->logged == true)
    {
      write_client(client->socket, "530 Can't change from user to guest");
    }
  else
    {
      if (client->s_token != NULL)
	{
	  client->user = strdup(client->s_token);
	}
      else
	client->user = "";
      write_client(client->socket, "331 Please specify the passs");
    }
}

void		manage_pass(t_client *client)
{
  if (!(client->user))
    write_client(client->socket, "503 Login with usr first");
  else if ((strcmp(client->user, "Anonymous") == 0) ||	\
	   (strcmp(client->user, "a") == 0))
    {
      write_client(client->socket, "230 Login successfull");
      client->logged = true;
    }
  else
    write_client(client->socket, "530 Login incorrect.");
}

void		manage_quit(t_client *client)
{
  (void)client;
}

void		manage_help(t_client *client)
{
  t_parser	*parser;

  parser = init();
  while (parser)
    {
      write(client->socket, parser->cmd, strlen(parser->cmd));
      write(client->socket, "\n", 1);
      parser = parser->next;
    }
  write_client(client->socket, "214 List of available commands");
}

void		manage_noop(t_client *client)
{
  write_client(client->socket, "200 noop");
}
