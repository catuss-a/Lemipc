/*
** enemy_in_player_range.c for enemy in player range in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Wed May 18 01:55:15 2011 axel catusse
** Last update Wed May 18 01:56:17 2011 axel catusse
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "lemipc.h"

static int		check_id_in_player_range(t_lemipc *lemipc,
						 t_coord2d *start,
						 t_coord2d *end,
						 t_coord2d *enemy)
{
  int			x;

  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  while (start->y < end->y)
    {
      x = start->x - 1;
      while (++x < end->x)
	{
	  if (lemipc->game->map[start->y][x] != EMPTY_CASE &&
	      lemipc->game->map[start->y][x] != lemipc->player.team)
	    {
	      enemy->x = x;
	      enemy->y = start->y;
	      if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
		return (ERROR_VALUE);
	      return (MESSAGE_TO_SEND);
	    }
	}
      ++start->y;
    }
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (SUCCESS_VALUE);
}

int			enemy_in_player_range(t_lemipc *lemipc, t_coord2d *enemy)
{
  t_coord2d		start;
  t_coord2d		end;

  start.x = lemipc->player.pos.x - PLAYER_RANGE;
  start.y = lemipc->player.pos.y - PLAYER_RANGE;
  if (start.x < 0)
    start.x = 0;
  if (start.y < 0)
    start.y = 0;
  end.x = lemipc->player.pos.x + PLAYER_RANGE;
  end.y = lemipc->player.pos.y + PLAYER_RANGE;
  if (end.x >= SIZE_W_CASE)
    end.x = SIZE_W_CASE;
  if (end.y >= SIZE_H_CASE)
    end.y = SIZE_H_CASE;
  return (check_id_in_player_range(lemipc, &start, &end, enemy));
}
