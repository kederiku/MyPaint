#ifndef __ACTION_H__
#define __ACTION_H__

#include <SDL/SDL.h>
#include "interface.h"
#include "tool.h"

typedef struct s_action : public c_interface
{
	bool		click;
	bool		etat;
	int		type_button;
	SDL_Rect	positionClic;
	SDL_Rect	positionDeplacement;
	SDL_Rect	positionRectangle;
	SDL_Event	event;
}	t_action;

void	wait_for_event(c_interface* init, s_action* action);
void	trace();
void	cut();
void	selection();
void	copy();
void	past();
void	change_brush();
void	new_page();
void	creat_popup(c_interface* init);
bool	click_button(SDL_Event event, c_interface* init, t_action* action);
void	print(c_interface* init, t_action* action);
bool	otion_bar(SDL_Event event, c_interface* init, t_action* action, c_tool* tool);

#endif
