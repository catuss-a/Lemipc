/*
** display_map.c for display in /home/catuss_a//workspace/lemipc
** 
** Made by axel catusse
** Login   <catuss_a@epitech.net>
** 
** Started on  Sun May 22 19:46:30 2011 axel catusse
** Last update Sun May 22 19:47:31 2011 axel catusse
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_rotozoom.h>
#include <sys/types.h>
#include "lemipc.h"

static void		blit_letter(SDL_Surface *sprite_letters,
				    SDL_Surface *screen, int x, int y, int team)
{
  SDL_Rect		coord;
  SDL_Rect		sprite;

  coord.x = x * SIZE_W_CASE;
  coord.y = y * SIZE_H_CASE;
  sprite.w = SIZE_W_CASE;
  sprite.h = SIZE_H_CASE;
  sprite.x = (team % 6) * SIZE_W_CASE;
  sprite.y = (team / 6) * SIZE_H_CASE;
  SDL_BlitSurface(sprite_letters, &sprite, screen, &coord);
}

int			display_map(t_lemipc *lemipc,
				    SDL_Surface *sprite_letters,
				    SDL_Surface *screen)
{
  int			x;
  int			y;
  int			team;

  y = -1;
  while (++y < MAP_SIZE_SIDE)
    {
      x = -1;
      while (++x < MAP_SIZE_SIDE)
	{
	  team = lemipc->game->map[y][x];
	  if (team != 0)
	    {
	      if (team > 25 || team < 1)
		{
		  fprintf(stderr,
			  "error: display_map: team number has to be in [1;25]\n");
		  return (ERROR_VALUE);
		}
	      else
		blit_letter(sprite_letters, screen, x, y, team);
	    }
	}
    }
  return (SUCCESS_VALUE);
}
