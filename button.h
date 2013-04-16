#ifndef __BUTTON_H__
#define	__BUTTON_H__

#include <SDL/SDL.h>
#include <iostream>
#include "interface.h"

class 	c_button : public c_interface
{
public:
	SDL_Surface*	button_new;
	SDL_Surface*	button_save;

	SDL_Surface*	button_pen;
	SDL_Surface*	button_brush;
	SDL_Surface*	button_load;
	SDL_Surface*	button_pipette;
	SDL_Surface*	button_less;
	SDL_Surface*	button_current_size;
	SDL_Surface*	button_plus;
	SDL_Surface*	button_padding;
	SDL_Surface*	button_rubber;
	SDL_Surface*	button_rectangle;
	SDL_Surface*	button_circle;
	SDL_Surface*	button_lineh;
	SDL_Surface*	button_linev;
	c_interface*	p;
	c_button();
	~c_button();
	char	creat_button(SDL_Surface* button, const char* file, int x, int y, int w, int h);
};

#endif
