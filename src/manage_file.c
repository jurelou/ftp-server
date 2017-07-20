/*
** manage_file.c for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Wed May 10 10:59:40 2017 jurczy_l
** Last update Sun May 21 18:46:30 2017 jurczy_l
*/

#include	"server.h"

void		manage_delete(t_client *client)
{
  if (client->logged)
    {
      if (client->s_token != NULL)
	{
	  if (remove(client->s_token) == -1)
	    write_client(client->socket, "552 Impossible to remove the file");
	  else
	    write_client(client->socket, "250 File correctly removed");
	}
      else
	write_client(client->socket, "501 You must enter a filename to remove");
    }
  else
    write_client(client->socket, "530 You must enter a filename to remove");
}

void		manage_retr(t_client *client)
{
  if (client->logged)
    {
      if (client->info.mode == NONE)
	write_client(client->socket, "520 Please use PASC or PORT first");
      else
	{
	  if (client->s_token != NULL)
	    write_client(client->socket, "200 Please use PASC or PORT first");
	  write_client(client->socket, "550 Please use PASC or PORT first");
	}
    }
  else
    write_client(client->socket, "530 You must enter a filename to remove");
}

void		manage_stor(t_client *client)
{
  if (client->logged)
    {
      if (client->info.mode == NONE)
	write_client(client->socket, "520 Please use PASC or PORT first");
      else
	{
	  if (client->s_token != NULL)
	    write_client(client->socket, "200 Please use PASC or PORT first");
	  write_client(client->socket, "550 Please use PASC or PORT first");
	}
    }
  else
    write_client(client->socket, "530 You must enter a filename to remove");
}
