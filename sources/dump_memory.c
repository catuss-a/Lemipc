/*
** dump_memory.c for dump in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 15 03:39:29 2011 axel catusse
** Last update Sun May 15 03:40:37 2011 axel catusse
*/

#include <stdio.h>
#include <sys/types.h>
#include "lemipc.h"

void			dump_memory(char **map)
{
  int			x;
  int			y;

  y = -1;
  while (++y < MAP_SIZE_SIDE)
    {
      x = -1;
      printf("line %03d:", y);
      while (++x < MAP_SIZE_SIDE)
	{
	  printf(" [%d] ", map[y][x]);
	}
      printf("\n");
    }
}
