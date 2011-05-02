#ifndef __AUDIO__

#define __AUDIO

#include <SDL/SDL_mixer.h>

void init_audio();

void play_wav(Mix_Chunk * wav);

void close_audio();

#endif
