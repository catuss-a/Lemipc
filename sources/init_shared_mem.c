/*
** init_shared_mem.c for init_sharedmem in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 15 03:37:27 2011 axel catusse
** Last update Sun May 22 19:15:53 2011 axel catusse
*/

#include <sys/param.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <getopt.h>
#include "lemipc.h"

int			init_game(t_lemipc *lemipc)
{
  int			y;
  union semun		semun;

  y = -1;
  while (++y < MAP_SIZE_SIDE)
    memset(lemipc->game->map[y], EMPTY_CASE, MAP_SIZE_SIDE);
  if ((lemipc->game->msg_id = msgget(lemipc->key, IPC_CREAT | SHM_R | SHM_W))
      == ERROR_VALUE)
    return (raise_error("msgget", ERROR_VALUE));
  if ((lemipc->game->sem_id = semget(lemipc->key, 1, IPC_CREAT | 0666))
      == ERROR_VALUE)
    return (raise_error("semget", ERROR_VALUE));
  semun.val = 1;
  if (semctl(lemipc->game->sem_id, 0, SETVAL, semun) == ERROR_VALUE)
    return (raise_error("semctl", ERROR_VALUE));
  return (SUCCESS_VALUE);
}

static int		create_shm(t_lemipc *lemipc)
{
  lemipc->shm_id = shmget(lemipc->key, sizeof(*lemipc->game),
			  IPC_CREAT | SHM_R | SHM_W);
  if (lemipc->shm_id == ERROR_VALUE)
    return (raise_error("shmget", ERROR_VALUE));
  lemipc->game = shmat(lemipc->shm_id, NULL, 0);
  if ((int)lemipc->game == ERROR_VALUE)
    return (raise_error("shmat", ERROR_VALUE));
  if (init_game(lemipc) == ERROR_VALUE)
    return (ERROR_VALUE);
  printf("shm created\n");
  return (SUCCESS_VALUE);
}

int			init_shared_mem(t_lemipc *lemipc)
{
  char			pathname[MAXPATHLEN];

  if (getcwd(pathname, MAXPATHLEN) == NULL)
    return (raise_error("getcwd", ERROR_VALUE));
  if ((lemipc->key = ftok(pathname, PROJ_ID)) == ERROR_VALUE)
    return (raise_error("ftok", ERROR_VALUE));
  lemipc->shm_id = shmget(lemipc->key, sizeof(*lemipc->game), SHM_R | SHM_W);
  printf("Try to create shm\n");
  if (lemipc->shm_id == ERROR_VALUE)
    {
      if (errno != ENOENT)
      	return (raise_error("shmget", ERROR_VALUE));
      if (create_shm(lemipc) == ERROR_VALUE)
	return (ERROR_VALUE);
    }
  else
    {
      printf("shm already created\n");
      if ((int)(lemipc->game = shmat(lemipc->shm_id, NULL, 0)) == ERROR_VALUE)
	return (raise_error("shmat", ERROR_VALUE));
    }
  return (SUCCESS_VALUE);
}
