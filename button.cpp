#include "button.h"
#include "interface.h"
#include "id.h"

c_button::c_button()
{
	this->button_new = NULL;
}

c_button::~c_button()
{
}

char    c_button::creat_button(SDL_Surface* button, const char *file, int x, int y, int w, int h)
{
	SDL_Rect	tmp;

	if (file == 0)
		return -1;
	tmp = id::change_pos(this->pos, x, y, w, h);
	this->pos = tmp;

	button = NULL;
	button = SDL_LoadBMP(file);
	if (button == NULL)
	{
		std::cout << "Button | creat_button | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_BlitSurface(button, NULL, get_screen(), &this->pos);
	SDL_UpdateRect(button, x, y, w, h);
	if (SDL_Flip(get_screen()) == - 1)
	{
		std::cout << "Button | creat_button | |Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	return 0;
}
