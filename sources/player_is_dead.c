/*
** player_is_dead.c for player dead in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Wed May 18 01:57:14 2011 axel catusse
** Last update Sun May 22 19:33:30 2011 axel catusse
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "lemipc.h"

static void		x_case(t_lemipc *lemipc, int *die)
{
  t_player		player;
  t_coord2d		pos;
  int			id;

  player = lemipc->player;
  pos = player.pos;
  if (pos.x > 0 && (id = GET_ID_FROM_MAP(lemipc, pos.x - 1, pos.y))
      != player.team
      && id != EMPTY_CASE)
    ++(*die);
  if (pos.x + 1 < SIZE_W_CASE
      && (id = GET_ID_FROM_MAP(lemipc, pos.x + 1, pos.y)) != player.team
      && id != EMPTY_CASE)
    ++(*die);
}

static void		y_case(t_lemipc *lemipc, int *die)
{
  t_player		player;
  t_coord2d		pos;
  int			id;

  player = lemipc->player;
  pos = player.pos;
  if (pos.y > 0 && (id = GET_ID_FROM_MAP(lemipc, pos.x, pos.y - 1))
      != player.team
      && id != EMPTY_CASE)
    ++(*die);
  if (pos.y + 1 < SIZE_H_CASE
      && (id = GET_ID_FROM_MAP(lemipc, pos.x, pos.y + 1)) != player.team
      && id != EMPTY_CASE)
    ++(*die);
}

int			player_is_dead(t_lemipc *lemipc)
{
  int			die;

  die = 0;
  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  x_case(lemipc, &die);
  y_case(lemipc, &die);
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  if (die >= 2)
    run = KO;
  return (SUCCESS_VALUE);
}
