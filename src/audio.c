#include "audio.h"

#include <SDL/SDL_mixer.h>

void
init_audio()
{
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 1, 4096 );
}

void
play_wav(Mix_Chunk * wav)
{
	Mix_PlayChannel(-1, wav, 0);
}

void
close_audio()
{
	Mix_CloseAudio();
}
