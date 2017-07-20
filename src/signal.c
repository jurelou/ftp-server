/*
** signal.c for Project-Master in /home/louis/Documents/PSU_2016_myftp
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Sun May 14 18:19:55 2017 jurczy_l
** Last update Sun May 14 18:20:47 2017 jurczy_l
*/

#include	"server.h"

void		interupt_handler()
{
  kill(0, SIGINT);
  exit(0);
}
