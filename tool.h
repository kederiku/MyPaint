#ifndef __TOOL_H__
#define __TOOL_H__

#include <SDL/SDL.h>
#include <iostream>
#include "interface.h"

class c_tool
{
public:

	c_tool();
	~c_tool();

	unsigned long	get_pixel(SDL_Surface* surface, int x, int y);
	void		set_pixel(SDL_Surface*	surface, int x, int y, unsigned long color);
	void		disk(SDL_Surface* surface, int cx, int cy, int rayon, unsigned long color);
	void		cercle(SDL_Surface* surface, int cx, int cy, int rayon, unsigned long color);
	void		rectangle(SDL_Surface* surface, int x, int y, int w, int h, unsigned long color);
	void		draw_line(SDL_Surface* surface, int source_x, int source_y, int dest_x, int dest_y, unsigned long color, c_interface* init);
	void		change_int(int* x, int* y);
	void		line_horizontal(SDL_Surface* surface, int x, int y, int size, unsigned long color);
	void		line_vertical(SDL_Surface* surface, int x, int y, int size, unsigned long color);
	int		id_abs(int x);
	void		pen(SDL_Surface* surface, int x, int y, int size, unsigned long color);
	void		painting(SDL_Surface* surface, int x, int y, c_interface* init);
	void		gum(SDL_Surface* surface, int  x, int y, int size);
	char		selection(SDL_Event event, c_interface* init);
//	char		selection(SDL_Event event, c_interface* init);
};

#endif
