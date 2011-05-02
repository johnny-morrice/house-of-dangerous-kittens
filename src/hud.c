#include "hud.h"
#include "sprite.h"
#include "zone.h"
#include "screen.h"

#include <SDL/SDL.h>
#include <stdlib.h>

#define text_gap 70

struct HUD
{
	SDL_Surface * digits[10];
	SDL_Surface * heart;
	SDL_Surface * minus;
	int * healthp;
};

HUD *
new_hud(int * healthp)
{
	HUD * display = (HUD *) zone(sizeof(HUD));
	display->digits[0] = load_sprite("data/sprites/digits/0.png");
	display->digits[1] = load_sprite("data/sprites/digits/1.png");
	display->digits[2] = load_sprite("data/sprites/digits/2.png");
	display->digits[3] = load_sprite("data/sprites/digits/3.png");
	display->digits[4] = load_sprite("data/sprites/digits/4.png");
	display->digits[5] = load_sprite("data/sprites/digits/5.png");
	display->digits[6] = load_sprite("data/sprites/digits/6.png");
	display->digits[7] = load_sprite("data/sprites/digits/7.png");
	display->digits[8] = load_sprite("data/sprites/digits/8.png");
	display->digits[9] = load_sprite("data/sprites/digits/9.png");
	display->heart = load_sprite("data/sprites/health.png");
	display->minus = load_sprite("data/sprites/digits/minus.png");
	display->healthp = healthp;
}

void
free_hud(HUD * display)
{
	unsigned int i;
	
	for (i = 0; i < 10; i++)
	{
		SDL_FreeSurface(display->digits[i]);
	}
	SDL_FreeSurface(display->heart);
	SDL_FreeSurface(display->minus);
}

void
hud_draw(HUD * display, SDL_Surface * screen)
{
	SDL_Rect dst;

	int health;
	unsigned int mag;
	unsigned int unit;
	unsigned int ten;
	unsigned int hundred;

	health = *(display->healthp);

	if (health == 100)
	{
		hundred = 1;
		unit = 0;
		ten = 0;
	}
	else
	{
		hundred = 0;
		
		mag = abs(health);
		unit = mag % 10;
		ten = ((mag - unit) / 10) % 10;
	}

	dst.x = 0;
	dst.y = screen_height - text_gap;

	SDL_BlitSurface(display->heart, NULL, screen, &dst);

	dst.x += text_gap;

	if (health < 0)
	{
		SDL_BlitSurface(display->minus, NULL, screen, &dst);
		dst.x += text_gap;
	}

	SDL_BlitSurface(display->digits[hundred], NULL, screen, &dst);
	dst.x += text_gap;

	SDL_BlitSurface(display->digits[ten], NULL, screen, &dst);
	dst.x += text_gap;

	SDL_BlitSurface(display->digits[unit], NULL, screen, &dst);
}
