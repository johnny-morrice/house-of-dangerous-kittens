#include "hud.h"
#include "sprite.h"
#include "zone.h"
#include "screen.h"
#include "player.h"

#include <SDL/SDL.h>
#include <stdlib.h>
#include <glib.h>

#define text_gap 70

struct HUD
{
	SDL_Surface * digits[10];
	SDL_Surface * heart;
	Player * player;
};

HUD *
new_hud(Player * player)
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
			printf("digit was %d\n", next);
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

	printf("drawing digit: %d\n", digit);

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

	printf("drawing digits\n");

	g_slist_foreach(digits, draw_digit, &draw);
}

void
hud_draw(HUD * display, SDL_Surface * screen)
{
	SDL_Rect dst;

	unsigned int health;

	GSList * health_digits;

	health = player_health(display->player);

	health_digits = to_digits(health);

	dst.x = 0;
	dst.y = screen_height - text_gap;

	SDL_BlitSurface(display->heart, NULL, screen, &dst);
	dst.x += text_gap;

	draw_digits(display, health_digits, screen, &dst);

	g_slist_free(health_digits);
}
