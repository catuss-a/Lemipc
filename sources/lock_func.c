/*
** lock_func.c for lock_func in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 15 03:57:20 2011 axel catusse
** Last update Mon May 16 18:21:44 2011 axel catusse
*/

#include <strings.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "lemipc.h"

int			lock_sem_id(int semid)
{
  struct sembuf		sops;

  bzero(&sops, sizeof(sops));
  sops.sem_op = -1;
  if (semop(semid, &sops, 1) == ERROR_VALUE)
    return (raise_error("lock_sem_id", ERROR_VALUE));
  return (SUCCESS_VALUE);
}

int			unlock_sem_id(int semid)
{
  struct sembuf		sops;

  bzero(&sops, sizeof(sops));
  sops.sem_op = 1;
  if (semop(semid, &sops, 1) == ERROR_VALUE)
    return (raise_error("lock_sem_id", ERROR_VALUE));
  return (SUCCESS_VALUE);
}
