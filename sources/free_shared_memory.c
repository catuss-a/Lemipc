/*
** free_shared_memory.c for free in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 22 18:51:38 2011 axel catusse
** Last update Sun May 22 19:02:39 2011 axel catusse
*/

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

static int		free_resources(t_lemipc *lemipc)
{
  if (msgctl(lemipc->game->msg_id, IPC_RMID, NULL) == ERROR_VALUE)
    return (SUCCESS_VALUE);
  if (semctl(lemipc->game->sem_id, 0, IPC_RMID) == ERROR_VALUE)
    return (ERROR_VALUE);
  if (shmdt(lemipc->game) < 0)
    return (ERROR_VALUE);
  if (shmctl(lemipc->shm_id, IPC_RMID, NULL) == ERROR_VALUE)
    return (ERROR_VALUE);
  return (SUCCESS_VALUE);
}

int			free_shared_resources(t_lemipc *lemipc)
{
  char			pathname[MAXPATHLEN];

  if (getcwd(pathname, MAXPATHLEN) == NULL)
    return (raise_error("getcwd", ERROR_VALUE));
  if ((lemipc->key = ftok(pathname, PROJ_ID)) == ERROR_VALUE)
    return (raise_error("ftok", ERROR_VALUE));
  lemipc->shm_id = shmget(lemipc->key, sizeof(*lemipc->game), SHM_R | SHM_W);
  if (lemipc->shm_id == ERROR_VALUE)
    return (raise_error("shmget", ERROR_VALUE));
  if ((int)(lemipc->game = shmat(lemipc->shm_id, NULL, 0)) == ERROR_VALUE)
    return (raise_error("shmat", ERROR_VALUE));
  if (init_game(lemipc) == ERROR_VALUE)
    return (ERROR_VALUE);
  if (free_resources(lemipc) == ERROR_VALUE)
    {
      return (ERROR_VALUE);
      printf("free shared resources: failed\n");
    }
  printf("free shared resources: success\n");
  return (SUCCESS_VALUE);
}
