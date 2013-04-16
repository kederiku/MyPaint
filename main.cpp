#include "interface.h"
#include "button.h"
#include "action.h"
#include "tool.h"

char	run(const char* name)
{
	t_action	action;
//	c_button	button;
	c_tool		tool;
	c_interface	init;

	if (init.run_surface(false, name) == 1)
		return 1;
	init.color_cursor = SDL_CreateRGBSurface(SDL_HWSURFACE,	5, 5, 32, 0, 0, 0, 0);
	if (init.color_cursor == NULL)
	{
		std::cout << "Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_EnableKeyRepeat(1, 1); //---> repetition touche active
	wait_for_event(&init, &action);
	return 0;
}

int main(int argc, char** argv)
{
	const char*	name;

	if (argc > 2)
		return -1;
	if (argc == 2)
	{
		name = (const char*)argv[1];
		if (run(name) == 1) 
		{
			std::cout << "this file doesn't exist" << std::endl;
			return -1;
		}
	}
	else
	{
		name = 0;
		run(0);
	}
	return 0;
}
