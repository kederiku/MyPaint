#include "action.h"


void	wait_for_event(c_interface* init, t_action* action)
{
	c_tool	tool;
	bool		tmp;

	SDL_Event	event;
	action->click = false;
	action->etat = false;
	action->type_button = 0;

	while(action->etat == false)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			std::cout << "quit legally" << std::endl;
			action->etat = true;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			action->click = false;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				action->type_button = 1;
				tmp = click_button(event, init, action);
				action->click = tmp;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				action->type_button = 2;
				tmp = click_button(event, init, action);
				action->click = tmp;
			}
		}
		else if (event.type == SDL_MOUSEMOTION &&
			 (event.motion.x >= 150) && (event.motion.y >= 25) &&
			 (event.motion.x <= init->work_w + 150) && (event.motion.y <= init->work_h + 25))
		{
			init->position_dest.x = event.motion.x - 150;
			init->position_dest.y = event.motion.y - 25;
			if (action->click == true)
			{
				print(init, action);
			}
		}
	}
	SDL_Quit();

}

bool	click_button(SDL_Event event, c_interface* init, t_action* action)
{
	c_tool	tool;

	if	((event.button.x >= 150) && (event.button.y >= 25) &&
		 (event.button.x <= init->work_w + 150) && (event.button.y <= init->work_h + 25))
	{
		init->position_source.x = event.button.x - 150;
		init->position_source.y = event.button.y - 25;
		if (action->type_button == 1)
		{
			if (init->type_tool == 2)
				tool.pen(init->work, init->position_source.x, init->position_source.y, init->size_tool, init->color_pen_left);
			else if (init->type_tool == 1)
				tool.disk(init->work, init->position_source.x, init->position_source.y, init->size_tool, init->color_pen_left);
			else if (init->type_tool == 8)
				tool.cercle(init->work, init->position_source.x, init->position_source.y, init->size_tool, init->color_pen_left);
			else if (init->type_tool == 9)
				tool.rectangle(init->work, init->position_source.x, init->position_source.y, init->size_tool * 2, init->size_tool, init->color_pen_left);
			print(init, action);
			action->click = true;
		}
		if (action->type_button == 2)
		{
			if (init->type_tool == 2)
				tool.pen(init->work, init->position_source.x, init->position_source.y, init->size_tool, init->color_pen_right);
			else if (init->type_tool == 1)
				tool.disk(init->work, init->position_source.x, init->position_source.y, init->size_tool, init->color_pen_right);
			else if (init->type_tool == 8)
				tool.cercle(init->work, init->position_source.x, init->position_source.y, init->size_tool, init->color_pen_right);
			else if (init->type_tool == 9)
				tool.rectangle(init->work, init->position_source.x, init->position_source.y, init->size_tool * 2, init->size_tool, init->color_pen_right);
			print(init, action);
			 action->click = true;
		}
	}
	else if ((event.motion.x >= 5) && (event.motion.y >= 1) &&
	    (event.motion.x <= 75) && (event.motion.y <= 24 && action->type_button == 1))
	{
		std::cout << "action | click_button | rezise" << std::endl;
		init->creat_new_popup();
		init->rezise_popup(event);
	}
	else if ((event.motion.x >= 81) && (event.motion.y >= 1) &&
	    (event.motion.x <= 151) && (event.motion.y <= 24 && action->type_button == 1))
	{
		std::cout << "action | click_button | save" << std::endl;
		init->creat_new_popup();
		init->save_popup(event);
	}
	else if ((event.motion.x >= 152) && (event.motion.y >= 1) &&
	    (event.motion.x <= 223) && (event.motion.y <= 24 && action->type_button == 1))
	{
		std::cout << "action | click_button | load" << std::endl;
		init->creat_new_popup();
		init->load_popup(event);
	}
	otion_bar(event, init, action, &tool);

	return action->click;
}

bool	otion_bar(SDL_Event event, c_interface* init, t_action* action, c_tool* tool)
{
	(void)action;

	if ((event.button.x >= 10) && (event.button.y >= 35) &&
	    (event.button.x <= 140) && (event.button.y <= 265))
	{
		init->position_source.x = event.button.x - 10;
		init->position_source.y = event.button.y - 35;
		if (action->type_button == 1)
		{
			init->color_pen_left = tool->get_pixel(init->get_palette(), init->position_source.x, init->position_source.y);
			SDL_FreeSurface(init->actu_color_left);
			init->creat_actu_color_left();
		}
		if (action->type_button == 2)
		{
			init->color_pen_right = tool->get_pixel(init->get_palette(), init->position_source.x, init->position_source.y);
			SDL_FreeSurface(init->actu_color_right);
			init->creat_actu_color_right();
		}
	}
	else if ((event.button.x >= 10) && (event.button.y >= 308) &&   // <--------button bruch
	    (event.button.x <= 43) && (event.button.y <= 338))
	{
		init->position_source.x = event.button.x - 10;
		init->position_source.y = event.button.y - 308;
		init->type_tool = 1;
		std::cout << "action | opion_bar | bruch" << std::endl;

	}
	else if ((event.button.x >= 48) && (event.button.y >= 308) &&    //  <----- button pen
	    (event.button.x <= 81) && (event.button.y <= 338))
	{
		init->position_source.x = event.button.x - 48;
		init->position_source.y = event.button.y - 308;
		init->type_tool = 2;
		std::cout << "action | opion_bar | pen" << std::endl;
	}
	else if ((event.button.x >= 86) && (event.button.y >= 308) &&    //  <----- button painting
	    (event.button.x <= 119) && (event.button.y <= 338))
	{
		init->position_source.x = event.button.x - 48;
		init->position_source.y = event.button.y - 308;
		init->type_tool = 4;
		std::cout << "action | opion_bar | painting" << std::endl;
	}
	else if ((event.button.x >= 10) && (event.button.y >= 270) &&    //  <----- button pipette
	    (event.button.x <= 43) && (event.button.y <= 303))
	{
		init->position_source.x = event.button.x - 43;
		init->position_source.y = event.button.y - 303;
		init->tmp_tool = init->type_tool;
		init->type_tool = 3;
		std::cout << "action | opion_bar | pipette" << std::endl;
	}
	else if ((event.button.x >= 10) && (event.button.y >= 347) &&    //  <----- button less
	    (event.button.x <= 43) && (event.button.y <= 380))
	{
		init->position_source.x = event.button.x - 10;
		init->position_source.y = event.button.y - 347;
		if (init->size_tool >= 2)
			init->size_tool = init->size_tool - 1;
		init->print_size();
		std::cout << "action | opion_bar | less" << std::endl;
	}
	else if ((event.button.x >= 48) && (event.button.y >= 347) &&    //  <----- button current_size
	    (event.button.x <= 81) && (event.button.y <= 380))
	{
		init->position_source.x = event.button.x - 48;
		init->position_source.y = event.button.y - 347;
		init->size_tool = 10;
		init->print_size();
		std::cout << "action | opion_bar | size 2" << std::endl;
	}
	else if ((event.button.x >= 87) && (event.button.y >= 347) &&    //  <----- button plus
	    (event.button.x <= 120) && (event.button.y <= 380))
	{
		init->position_source.x = event.button.x - 87;
		init->position_source.y = event.button.y - 347;
		if (init->size_tool <= 45)
			init->size_tool = init->size_tool + 1;
		init->print_size();
		std::cout << "action | opion_bar | plus" << std::endl;
	}
	else if ((event.button.x >= 10) && (event.button.y >= 385) &&    //  <----- button rubber
	    (event.button.x <= 43) && (event.button.y <= 418))
	{
		init->position_source.x = event.button.x - 10;
		init->position_source.y = event.button.y - 385;
		init->tmp_tool = init->type_tool;
		init->type_tool = 5;
		std::cout << "action | opion_bar | rubber " << std::endl;
	}
	else if ((event.button.x >= 48) && (event.button.y >= 385) &&    //  <----- button rectangle
	    (event.button.x <= 81) && (event.button.y <= 418))
	{
		init->position_source.x = event.button.x - 48;
		init->position_source.y = event.button.y - 385;
		init->tmp_tool = init->type_tool;
		init->type_tool = 9;
		std::cout << "action | opion_bar | rectangle " << std::endl;
	}
	else if ((event.button.x >= 87) && (event.button.y >= 385) &&    //  <----- button cercle
	    (event.button.x <= 120) && (event.button.y <= 418))
	{
		init->position_source.x = event.button.x - 87;
		init->position_source.y = event.button.y - 385;
		init->tmp_tool = init->type_tool;
		init->type_tool = 8;
		std::cout << "action | opion_bar | the ring " << std::endl;
	}
	else if ((event.button.x >= 10) && (event.button.y >= 423) &&    //  <----- button lineh
	    (event.button.x <= 43) && (event.button.y <= 456))
	{
		init->position_source.x = event.button.x - 10;
		init->position_source.y = event.button.y - 423;
		init->tmp_tool = init->type_tool;
		init->type_tool = 6;
		std::cout << "action | opion_bar | line horizontal " << std::endl;
	}
	else if ((event.button.x >= 48) && (event.button.y >= 423) &&    //  <----- button linev
	    (event.button.x <= 81) && (event.button.y <= 456))
	{
		init->position_source.x = event.button.x - 48;
		init->position_source.y = event.button.y - 423;
		init->tmp_tool = init->type_tool;
		init->type_tool = 7;
		std::cout << "action | opion_bar | line vertical " << std::endl;
	}
	return true;
}

void	print(c_interface* init, t_action* action)
{
	c_tool	tool;
	if (init->type_tool == 3)
	{
		if (action->type_button == 1)
		{
			init->color_pen_left = tool.get_pixel(init->work, init->position_source.x, init->position_source.y);
			SDL_FreeSurface(init->actu_color_left);
			init->creat_actu_color_left();
			init->type_tool = init->tmp_tool;
			tool.draw_line(init->work, init->position_source.x, init->position_source.y, init->position_dest.x, init->position_dest.y    , init->color_pen_left, init);
		}
		if (action->type_button == 2)
		{
			init->color_pen_right = tool.get_pixel(init->work, init->position_source.x, init->position_source.y);
			SDL_FreeSurface(init->actu_color_right);
			init->creat_actu_color_right();
			init->type_tool = init->tmp_tool;
			tool.draw_line(init->work, init->position_source.x, init->position_source.y, init->position_dest.x, init->position_dest.y    , init->color_pen_right, init);
		}
	}
	if (action->type_button == 1)
		tool.draw_line(init->work, init->position_source.x, init->position_source.y, init->position_dest.x, init->position_dest.y    , init->color_pen_left, init);
	if (action->type_button == 2)
		tool.draw_line(init->work, init->position_source.x, init->position_source.y, init->position_dest.x, init->position_dest.y    , init->color_pen_right, init);
	init->position_source.x = init->position_dest.x;
	init->position_source.y = init->position_dest.y;
	SDL_BlitSurface(init->work, NULL, init->get_screen(), &init->work_pos);
	if (SDL_Flip(init->get_screen()) == -1)
	{
		std::cout << "action | print |Error: " << SDL_GetError() << std::endl;
		return;
	}
}
