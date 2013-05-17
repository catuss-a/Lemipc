/*
** launch_lemipc.c for launch in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Mon May 16 01:02:34 2011 axel catusse
** Last update Sun May 22 19:19:02 2011 axel catusse
*/

#include <time.h>
#include <sys/param.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include "lemipc.h"

char			run = OK;

static void		catch_parent_sig(int sig)
{
  (void)sig;
  printf("signal catch. leave parent\n");
  run = KO;
}

static int		set_start_game(t_lemipc *lemipc,
				       int mode)
{
  if (lock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  lemipc->game->start_game = mode;
  if (unlock_sem_id(lemipc->game->sem_id) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (SUCCESS_VALUE);
}

static int		lemipc_loop(t_lemipc *lemipc)
{
  int			ret;

  srand(time(NULL));
  while (run == OK)
    {
      if (lemipc->game->start_game == OK)
	{
	  if ((ret = end_game(lemipc)) == ERROR_VALUE)
	    return (ERROR_VALUE);
	  if (ret == QUIT)
	    lemipc->game->start_game = QUIT;
	  if ((ret = player_is_dead(lemipc)) == ERROR_VALUE)
	    return (ERROR_VALUE);
	  if (ret < 2)
	    if (player_move(lemipc) == ERROR_VALUE)
	      return (ERROR_VALUE);
	}
      else if (lemipc->game->start_game == QUIT)
	run = KO;
      usleep(100000);
    }
  return (SUCCESS_VALUE);
}

int			launch_lemipc(t_lemipc *lemipc)
{
  int			nb_of_player;

  if ((int)signal(SIGINT, catch_parent_sig) == ERROR_VALUE)
    run = KO;
  if (set_player_position(lemipc) == ERROR_VALUE)
    run = KO;
  if ((lemipc->opt & FLAG_START) == FLAG_START)
    if (set_start_game(lemipc, OK) == ERROR_VALUE)
      run = KO;
  if ((lemipc->opt & FLAG_QUIT) == FLAG_QUIT)
    if (set_start_game(lemipc, QUIT) == ERROR_VALUE)
      run = KO;
  if (lemipc_loop(lemipc) == ERROR_VALUE)
    return (ERROR_VALUE);
  (void)delete_player_from_map(lemipc);
  nb_of_player = count_player(lemipc, ALL_PLAYER);
  if (nb_of_player == ERROR_VALUE)
    return (ERROR_VALUE);
  else if (nb_of_player == 0)
    {
      printf("Winner: Team %d - free_ipcs ...\n", lemipc->player.team);
      if (free_ipcs(lemipc) == ERROR_VALUE)
	return (ERROR_VALUE);
    }
  return (SUCCESS_VALUE);
}
