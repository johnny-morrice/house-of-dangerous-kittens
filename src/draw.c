#include "draw.h"
#include "zone.h"
#include "screen.h"

#include <SDL/SDL.h>

struct Camera
{
	float xoffset;
	float yoffset;
};

Camera *
new_camera()
{
	return (Camera *) zone(sizeof(Camera));
}

void
camera_centre(Camera * cam, float x, float y)
{
	float realx, realy;
	float centrex, centrey;
	
	realx = square_size * x;
	realy = square_size * y;

	centrex = screen_width / 2;
	centrey = screen_height / 2;

	cam->xoffset = centrex - realx;
	cam->yoffset = centrey - realy;

}

void
draw(SDL_Surface * sprite, SDL_Surface * canvas, Camera * cam, float x, float y)
{
	SDL_Rect offset;
	offset.x = x * square_size + cam->xoffset;
	offset.y = y * square_size + cam->yoffset;
	SDL_BlitSurface(sprite, NULL, canvas, &offset);
}
