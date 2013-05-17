/*
** count_func.c for count_func in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 15 03:54:47 2011 axel catusse
** Last update Sun May 22 19:15:10 2011 axel catusse
*/

#include <sys/types.h>
#include "lemipc.h"

static void		inc_cpt(player_type count_what,
				int id,
				int team,
				int *cpt)
{
  if (count_what == ALL_PLAYER)
    *cpt += 1;
  else if (count_what == MATE_PLAYER && id == team)
    *cpt += 1;
  else if (count_what == ENEMY_PLAYER && id != team)
    *cpt += 1;
}

int			count_player(t_lemipc *lemipc,
				     player_type count_what)
{
  int			cpt;
  int			x;
  int			y;

  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  cpt = 0;
  y = -1;
  while (++y < MAP_SIZE_SIDE)
    {
      x = -1;
      while (++x < MAP_SIZE_SIDE)
	{
	  if (lemipc->game->map[y][x] != EMPTY_CASE)
	    inc_cpt(count_what, lemipc->game->map[y][x],
		    lemipc->player.team, &cpt);
	}
    }
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (cpt);
}

int			count_id_map(t_lemipc *lemipc, int id)
{
  int			cpt;
  int			x;
  int			y;

  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  cpt = 0;
  y = -1;
  while (++y < MAP_SIZE_SIDE)
    {
      x = -1;
      while (++x < MAP_SIZE_SIDE)
	if (lemipc->game->map[y][x] == id)
	  cpt += 1;
    }
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (cpt);
}
