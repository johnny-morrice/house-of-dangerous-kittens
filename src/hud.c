#include "hud.h"
#include "sprite.h"
#include "zone.h"
#include "screen.h"
#include "player.h"
#include "timetrack.h"
#include "control.h"

#include <SDL/SDL.h>
#include <stdlib.h>
#include <glib.h>

#define text_gap 40

#define DIGIT_FORE "data/sprites/digits/"
#define LETTER_FORE "data/sprites/letters/"
#define DEAD_PATH "data/sprites/dead.png"
#define HEALTH_PATH "data/sprites/health.png"

#define DIGIT_PATH(path) DIGIT_FORE path
#define LETTER_PATH(path) LETTER_FORE path

struct HUD
{
	SDL_Surface * digits[10];
	SDL_Surface * heart;
	SDL_Surface * f;
	SDL_Surface * p;
	SDL_Surface * s;
	SDL_Surface * c;
	SDL_Surface * o;
	SDL_Surface * r;
	SDL_Surface * e;
	SDL_Surface * a;
	SDL_Surface * u;
	SDL_Surface * d;
	SDL_Surface * dead;
	Player * player;
	TimeTracker * time;
	Control * halter;
};

HUD *
new_hud(Player * player, TimeTracker * time, Control * halter)
{
	HUD * display = (HUD *) zone(sizeof(HUD));
	display->digits[0] = load_sprite(DIGIT_PATH("0.png"));
	display->digits[1] = load_sprite(DIGIT_PATH("1.png"));
	display->digits[2] = load_sprite(DIGIT_PATH("2.png"));
	display->digits[3] = load_sprite(DIGIT_PATH("3.png"));
	display->digits[4] = load_sprite(DIGIT_PATH("4.png"));
	display->digits[5] = load_sprite(DIGIT_PATH("5.png"));
	display->digits[6] = load_sprite(DIGIT_PATH("6.png"));
	display->digits[7] = load_sprite(DIGIT_PATH("7.png"));
	display->digits[8] = load_sprite(DIGIT_PATH("8.png"));
	display->digits[9] = load_sprite(DIGIT_PATH("9.png"));

	display->f = load_sprite(LETTER_PATH("f.png"));
	display->p = load_sprite(LETTER_PATH("p.png"));
	display->s = load_sprite(LETTER_PATH("s.png"));
	display->c = load_sprite(LETTER_PATH("c.png"));
	display->o = load_sprite(LETTER_PATH("o.png"));
	display->r = load_sprite(LETTER_PATH("r.png"));
	display->e = load_sprite(LETTER_PATH("e.png"));
	display->a = load_sprite(LETTER_PATH("a.png"));
	display->u = load_sprite(LETTER_PATH("u.png"));
	display->d = load_sprite(LETTER_PATH("d.png"));

	display->dead = load_sprite(DEAD_PATH);
	display->heart = load_sprite(HEALTH_PATH);

	display->time = time;

	display->player = player;
	display->halter = halter;

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
	SDL_FreeSurface(display->c);
	SDL_FreeSurface(display->o);
	SDL_FreeSurface(display->r);
	SDL_FreeSurface(display->e);
	SDL_FreeSurface(display->u);
	SDL_FreeSurface(display->d);
	SDL_FreeSurface(display->dead);
}

GSList *
to_digits(unsigned int num)
{
	GSList * digits = NULL;

	unsigned int next;

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
	unsigned int score;

	GSList * health_digits;
	GSList * fps_digits;
	GSList * score_digits;

	health = player_health(display->player);
	score = player_score(display->player);
	frames = fps(display->time);

	health_digits = to_digits(health);
	fps_digits = to_digits(frames);
	score_digits = to_digits(score);

	dst.x = 0;
	dst.y = 0;

	SDL_BlitSurface(display->f, NULL, screen, &dst);
	dst.x += text_gap;

	SDL_BlitSurface(display->p, NULL, screen, &dst);
	dst.x += text_gap;

	SDL_BlitSurface(display->s, NULL, screen, &dst);
	dst.x += text_gap * 2;

	draw_digits(display, fps_digits, screen, &dst);

	if (health == 0)
	{
		dst.x = 0;
		dst.y = text_gap;
		SDL_BlitSurface(display->dead, NULL, screen, &dst);
	}

	if (is_paused(display->halter))
	{
		dst.x = screen_width / 2;
		dst.y = screen_height / 2;
		SDL_BlitSurface(display->p, NULL, screen, &dst);
		dst.x += text_gap;
		SDL_BlitSurface(display->a, NULL, screen, &dst);
		dst.x += text_gap;
		SDL_BlitSurface(display->u, NULL, screen, &dst);
		dst.x += text_gap;
		SDL_BlitSurface(display->s, NULL, screen, &dst);
		dst.x += text_gap;
		SDL_BlitSurface(display->e, NULL, screen, &dst);
		dst.x += text_gap;
		SDL_BlitSurface(display->d, NULL, screen, &dst);
		dst.x += text_gap;
		
	}

	dst.x = 0;
	dst.y = screen_height - text_gap;

	SDL_BlitSurface(display->heart, NULL, screen, &dst);
	dst.x += text_gap;

	draw_digits(display, health_digits, screen, &dst);

	dst.x = screen_width / 2;

	SDL_BlitSurface(display->s, NULL, screen, &dst);

	dst.x += text_gap;

	SDL_BlitSurface(display->c, NULL, screen, &dst);

	dst.x += text_gap;

	SDL_BlitSurface(display->o, NULL, screen, &dst);

	dst.x += text_gap;

	SDL_BlitSurface(display->r, NULL, screen, &dst);

	dst.x += text_gap;

	SDL_BlitSurface(display->e, NULL, screen, &dst);

	dst.x += text_gap * 2;

	draw_digits(display, score_digits, screen, &dst);

	g_slist_free(health_digits);
	g_slist_free(fps_digits);
	g_slist_free(score_digits);
}
