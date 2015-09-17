# House of Dangerous Kittens

A topdown shooting game in C.  An entry for Ludum Dare 20.

## Credits

Copyright 2011 John Morrice

Contact: john@functorama.com

## Requirements

* SDL 1.2
* SDL\_mixer 1.2
* SDL\_image 1.2
* Glib (gobject)
* gcc
* rake

I found that on a new Ubuntu 14.04 install, I could build the game after

    $ sudo apt-get install libsdl-mixer1.2-dev libsdl-image1.2-dev

## Play the game:

    $ rake play

After compilation, the binary is placed in work/kittens

## Controls:

Move the player using the directional keys or WASD

Click to shoot

Press p to pause

Escape to quit

## Legal

Released under the terms of the GNU GPLv3.  See COPYING for more details.
