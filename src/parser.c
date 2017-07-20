/*
** parser.c for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Wed May 10 10:00:52 2017 jurczy_l
** Last update Sun May 21 18:08:20 2017 jurczy_l
*/

#include	"server.h"

t_parser	*add(char *cmd, cmd_ptr ptr)
{
  t_parser	*unit;

  if ((unit = malloc(sizeof(t_parser))) == NULL)
    return (NULL);
  unit->cmd = strdup(cmd);
  unit->ptr = ptr;
  unit->next = NULL;
  return (unit);
}

char		**get_cmd_name()
{
  char		**res;

  if ((res = malloc(sizeof(char *) * (NB_COMMANDS + 1))) == NULL)
    return (NULL);
  res[0] = strdup("USER");
  res[1] = strdup("PASS");
  res[2] = strdup("CWD");
  res[3] = strdup("CDUP");
  res[4] = strdup("QUIT");
  res[5] = strdup("DELE");
  res[6] = strdup("PWD");
  res[7] = strdup("PASV");
  res[8] = strdup("PORT");
  res[9] = strdup("HELP");
  res[10] = strdup("NOOP");
  res[11] = strdup("RETR");
  res[12] = strdup("STOR");
  res[13] = strdup("LIST");
  res[14] = NULL;
  return (res);
}

cmd_ptr		*init_tab()
{
  cmd_ptr	*tab_ptr;

  if ((tab_ptr = malloc(sizeof(cmd_ptr) * (NB_COMMANDS + 1))) == NULL)
    return (NULL);
  tab_ptr[0] = manage_user;
  tab_ptr[1] = manage_pass;
  tab_ptr[2] = manage_cwd;
  tab_ptr[3] = manage_cdup;
  tab_ptr[4] = manage_quit;
  tab_ptr[5] = manage_delete;
  tab_ptr[6] = manage_pwd;
  tab_ptr[7] = manage_pasv;
  tab_ptr[8] = manage_port;
  tab_ptr[9] = manage_help;
  tab_ptr[10] = manage_noop;
  tab_ptr[11] = manage_retr;
  tab_ptr[12] = manage_stor;
  tab_ptr[13] = manage_list;
  tab_ptr[14] = NULL;
  return (tab_ptr);
}

t_parser	*init()
{
  t_parser	*parser;
  t_parser	*curs;
  char		**cmd_name;
  cmd_ptr	*ptr;
  int		i;

  ptr = init_tab();
  cmd_name = get_cmd_name();
  i = 1;
  parser = add(cmd_name[0], ptr[0]);
  curs = parser;
  while (cmd_name[i] != NULL)
    {
      curs->next = add(cmd_name[i], ptr[i]);
      i++;
      curs = curs->next;
    }
  return (parser);
}
