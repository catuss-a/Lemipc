/*
** main.c for main in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sat May 14 19:30:45 2011 axel catusse
** Last update Sun May 22 19:59:07 2011 axel catusse
*/

#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "lemipc.h"

static void		print_usage(char *bin)
{
  fprintf(stderr, "Usage: %s -t id_team [-v] [-s] [-q]\n\n", bin);
  fprintf(stderr, "- OPTIONS ---------------------------------------\n");
  fprintf(stderr, "-t : team number (mandatory)\n");
  fprintf(stderr, "-v : verbose on the process (SDL graphic)\n");
  fprintf(stderr, "-s : start the game\n");
  fprintf(stderr, "-q : quit the game and free shared resources\n");
  fprintf(stderr, "-r : free shared resources \n\n");
}

int			main(int argc, char **argv)
{
  t_lemipc		lemipc;

  if (argc < 2)
    {
      print_usage(argv[0]);
      return (EXIT_FAILURE);
    }
  bzero(&lemipc, sizeof(lemipc));
  if (check_option(&lemipc, argc, argv) == ERROR_VALUE)
    {
      print_usage(argv[0]);
      return (EXIT_FAILURE);
    }
  if ((lemipc.opt & FLAG_FREE) == FLAG_FREE)
    return (free_shared_resources(&lemipc));
  if ((lemipc.opt & FLAG_VERBOSE) == FLAG_VERBOSE)
    if (fork_to_start_graphic(&lemipc) == ERROR_VALUE)
      return (ERROR_VALUE);
  if (init_shared_mem(&lemipc) == ERROR_VALUE)
    return (EXIT_FAILURE);
  if (launch_lemipc(&lemipc) == ERROR_VALUE)
    return (EXIT_FAILURE);
  printf("program's exiting correctly\n");
  return (EXIT_SUCCESS);
}
