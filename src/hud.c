#include "hud.h"
#include "sprite.h"
#include "zone.h"
#include "screen.h"
#include "player.h"
#include "timetrack.h"

#include <SDL/SDL.h>
#include <stdlib.h>
#include <glib.h>

#define text_gap 70

struct HUD
{
	SDL_Surface * digits[10];
	SDL_Surface * heart;
	SDL_Surface * f;
	SDL_Surface * p;
	SDL_Surface * s;
	Player * player;
	TimeTracker * time;
};

HUD *
new_hud(Player * player, TimeTracker * time)
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

	display->f = load_sprite("data/sprites/letters/f.png");
	display->p = load_sprite("data/sprites/letters/p.png");
	display->s = load_sprite("data/sprites/letters/s.png");

	display->time = time;

	display->heart = load_sprite("data/sprites/health.png");
	display->player = player;

	return display;
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
	SDL_FreeSurface(display->f);
	SDL_FreeSurface(display->p);
	SDL_FreeSurface(display->s);
}

GSList *
to_digits(unsigned int num)
{
	GSList * digits = NULL;

	unsigned int next;

	printf("Digits:\n");

	if (num == 0)
	{
		digits = g_slist_prepend(digits, GINT_TO_POINTER(0));
	}
	else
	{
		while (num > 0)
		{
			next = num % 10;
			num = (num - next) / 10;
			digits = g_slist_prepend(digits, GINT_TO_POINTER(next));
		}
	}

	return digits;
}

struct DigitDraw
{
	HUD * display;
	SDL_Surface * screen;
	SDL_Rect * dst;

};

void
draw_digit(gpointer digitp, gpointer drawp)
{
	unsigned int digit = GPOINTER_TO_INT(digitp);


	struct DigitDraw * draw = (struct DigitDraw *) drawp;

	SDL_Rect * dst = draw->dst;

	SDL_Surface * screen = draw->screen;

	HUD * display = draw->display;

	SDL_BlitSurface(display->digits[digit], NULL, screen, dst);
	dst->x += text_gap;

}

void
draw_digits(HUD * display, GSList * digits, SDL_Surface * screen, SDL_Rect * dst)
{
	struct DigitDraw draw;
	draw.display = display;
	draw.screen = screen;
	draw.dst = dst;

	g_slist_foreach(digits, draw_digit, &draw);
}

void
hud_draw(HUD * display, SDL_Surface * screen)
{
	SDL_Rect dst;

	unsigned int health;
	unsigned int frames;

	GSList * health_digits;
	GSList * fps_digits;

	health = player_health(display->player);
	frames = fps(display->time);

	health_digits = to_digits(health);
	fps_digits = to_digits(frames);

	dst.x = 0;
	dst.y = screen_height - text_gap;

	SDL_BlitSurface(display->heart, NULL, screen, &dst);
	dst.x += text_gap;

	draw_digits(display, health_digits, screen, &dst);

	dst.x = screen_width / 2; 

	SDL_BlitSurface(display->f, NULL, screen, &dst);
	dst.x += text_gap;

	SDL_BlitSurface(display->p, NULL, screen, &dst);
	dst.x += text_gap;

	SDL_BlitSurface(display->s, NULL, screen, &dst);
	dst.x += text_gap;

	draw_digits(display, fps_digits, screen, &dst);

	g_slist_free(health_digits);
	g_slist_free(fps_digits);
}
