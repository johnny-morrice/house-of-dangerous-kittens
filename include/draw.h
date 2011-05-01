#ifndef __DRAW__

#define __DRAW__

#include <SDL/SDL.h>

// Size of each tile in pixels
#define square_size 64

typedef struct Camera Camera;

Camera *
new_camera();

// Center the camera on this position
void
camera_centre(Camera * cam, float x, float y);

void
draw(SDL_Surface * thing, SDL_Surface * canvas, Camera * cam, float x, float y);


#endif
