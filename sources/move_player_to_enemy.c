/*
** move_player_to_enemy.c for move in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 22 18:05:40 2011 axel catusse
** Last update Sun May 22 19:26:45 2011 axel catusse
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "lemipc.h"

static int		move_to(t_lemipc *lemipc, int x, int y)
{
  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  if (GET_ID_FROM_MAP(lemipc, x, y) == EMPTY_CASE)
    {
      lemipc->game->map[lemipc->player.pos.y][lemipc->player.pos.x]
	= EMPTY_CASE;
      lemipc->game->map[y][x] = lemipc->player.team;
      lemipc->player.pos.x = x;
      lemipc->player.pos.y = y;
      if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
	return (ERROR_VALUE);
      return (MOVED);
    }
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (SUCCESS_VALUE);
}

static int		check_distance(t_lemipc *lemipc, t_coord2d *enemy,
				       t_coord2d *vector, t_coord2d *pos)
{
  int			h;
  int			w;
  int			ret;

  w = abs(pos->x - enemy->x);
  h = abs(pos->y - enemy->y);
  if (w >= h)
    {
      if ((ret = move_to(lemipc, pos->x + vector->x, pos->y)) == ERROR_VALUE)
	return (ERROR_VALUE);
      else if (ret == MOVED)
	return (SUCCESS_VALUE);
    }
  if (w <= h)
    {
      if ((ret = move_to(lemipc, pos->x, pos->y + vector->y)) == ERROR_VALUE)
	return (ERROR_VALUE);
      else if (ret == MOVED)
	return (SUCCESS_VALUE);
    }
  return (SUCCESS_VALUE);
}

int			move_player_to_enemy(t_lemipc *lemipc, t_coord2d *enemy)
{
  t_coord2d		*pos;
  t_coord2d		vector;

  vector.x = 0;
  vector.y = 0;
  pos = &lemipc->player.pos;
  if (pos->y != enemy->y)
    vector.y = pos->y < enemy->y ? 1 : -1;
  if (pos->x != enemy->x)
    vector.x = pos->x < enemy->x ? 1 : -1;
  return (check_distance(lemipc, enemy, &vector, pos));
}
