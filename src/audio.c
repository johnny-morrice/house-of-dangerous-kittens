/* Copyright 2011 John Morrice
 *
 * Contact spoon@killersmurf.com
 *
 * This file is part of Dangerous Kittens.
 *
 * Dangerous Kittens is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dangerous Kittens is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dangerous Kittens.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
