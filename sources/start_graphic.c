/*
** start_graphic.c for start_graphic in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 15 22:29:59 2011 axel catusse
** Last update Sun May 22 19:51:54 2011 axel catusse
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <sys/types.h>
#include "lemipc.h"

char			live = OK;

void			catch_son_sig(int sig)
{
  if (sig == SIGINT)
    live = KO;
}

static int		graphic_loop(t_lemipc *lemipc,
				     SDL_Surface *sprite_letters,
				     SDL_Surface *screen)
{
  if ((int)signal(SIGINT, catch_son_sig) == ERROR_VALUE)
    return (raise_error("signal", ERROR_VALUE));
  while (live && lemipc->game->start_game != QUIT)
    {
      SDL_FillRect(screen, NULL,
		   SDL_MapRGB(screen->format, 255, 0, 255));
      handle_event();
      if (display_map(lemipc, sprite_letters, screen) == ERROR_VALUE)
	live = KO;
      SDL_Flip(screen);
      usleep(10000);
    }
  return (SUCCESS_VALUE);
}

int			start_graphic(t_lemipc *lemipc)
{
  SDL_Surface		*sprite_letters;
  SDL_Surface		*screen;

  if (SDL_Init(SDL_INIT_VIDEO) == ERROR_VALUE)
    return (raise_error("SDL_Init", ERROR_VALUE));
  screen = SDL_SetVideoMode(SIZE_W_CASE * MAP_SIZE_SIDE,
			    SIZE_H_CASE * MAP_SIZE_SIDE, 32, SDL_HWSURFACE);
  sprite_letters = x_IMG_Load("./imgs/letters.gif");
  if (init_shared_mem(lemipc) == ERROR_VALUE)
    return (ERROR_VALUE);
  (void)graphic_loop(lemipc, sprite_letters, screen);
  (void)SDL_FreeSurface(sprite_letters);
  SDL_Quit();
  return (SUCCESS_VALUE);
}
