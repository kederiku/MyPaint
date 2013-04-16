#include <unistd.h>
#include "interface.h"
#include "button.h"
#include "id.h"

c_interface::c_interface()
{
	SDL_Init(SDL_INIT_VIDEO);
	this->save_temp = "save_me.bmp";
	this->color_pen_left = 0;
	this->color_pen_right= 0;
	this->type_tool = 2;
	this->size_tool = 10;
	this->work_w = 745;
	this->work_h = 610;
	this->w_screen = (this->work_w + 155);
	this->h_screen = (this->work_h + 30);
	this->screen = SDL_SetVideoMode(this->w_screen, this->h_screen, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
	this->save1 = this->work_w;
	this->save2 = this->work_h;
	this->param1 = NULL;
	this->param2 = NULL;
	this->pos.x = 0;
	this->pos.y = 0;
	this->pos.w = 0;
	this->pos.h = 0;
	this->buffer = NULL;
	this->work = NULL;
	this->name_change = 0;
}

c_interface::~c_interface()
{
	delete [] this->buffer;
	delete [] this->param1;
	delete [] this->param2;
}

char	c_interface::creat_window()
{
	if (this->screen != NULL)
		SDL_FreeSurface(this->screen);
	this->screen = SDL_SetVideoMode(this->w_screen, this->h_screen, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
	if (this->screen == NULL)
	{
		std::cout << "Interface | Error ->creat_window : " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_WM_SetCaption("MyPaint", NULL);
	if (SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0)) == -1)
	{
		std::cout << "Interface | Error ->creat_window: " << SDL_GetError() << std::endl;
		return -1;
	}
	return 0;
}

char	c_interface::creat_work_resize()
{
	SDL_Rect	tmp;

	std::cout << "creat_work_resize | width : "<< this->work_w << " | height : " << this->work_h << std::endl;

	tmp = id::change_pos(this->pos, 150, 25, this->work_w, this->work_h);
	this->pos = tmp;
	work_pos.x = tmp.x;
	work_pos.y = tmp.y;

	SDL_FreeSurface(this->work);
	this->work = SDL_CreateRGBSurface(SDL_HWSURFACE, this->work_w, this->work_h,32 ,0,0,0,0);
	if (this->work == NULL)
	{
		std::cout << "Interface | Error ->creat_work_resize: " << SDL_GetError() << std::endl;
		return -1;
	}
	if (SDL_FillRect(this->work, NULL, SDL_MapRGB(this->work->format, 255, 255, 255)) == -1)
	{
		std::cout << "Interface | Error ->creat_work_resize: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_BlitSurface(this->work, NULL, this->screen, &this->pos);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | Error-> creat_work_resize: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_UpdateRect(this->screen, 0, 0, this->w_screen, this->h_screen);
	SDL_UpdateRect(this->work, 150, 25, this->work_w, 610);
	return 0;
}

char	c_interface::creat_work(const char* name = 0)
{
	SDL_Rect	tmp;
	SDL_Surface*	copy;

	tmp = id::change_pos(this->pos, 150, 25, this->work_w, this->work_h);
	this->pos = tmp;
	work_pos.x = tmp.x;
	work_pos.y = tmp.y;

	if (name != 0 && this->name_change == 0)
	{
		this->work = SDL_LoadBMP(name);
		if (this->work == NULL)
		{
			std::cout << "Interface | Error->creat_work: " << SDL_GetError() << std::endl;
			return -1;
		}
		else
		{
			copy = SDL_CreateRGBSurface(SDL_HWSURFACE,this->work->w,this->work->h,32,0,0,0,0);
			if (copy == NULL)
			{
				std::cout << "Interface | Error->creat_work: " << SDL_GetError() << std::endl;
				return -1;
			}
			SDL_BlitSurface(this->work,NULL,copy,0);
			SDL_FreeSurface(this->work);
			this->work = copy;
			this->work_w = this->work->w;
			this->work_h = this->work->h;
			this->save1 = this->work_w;
			this->save2 = this->work_h;
			std::cout << this->work_w << this->work_h << std::endl;
		}
		this->name_change += 1;
	}
	if (this->work == NULL)
	{
		this->work = SDL_CreateRGBSurface(SDL_HWSURFACE, this->work_w, this->work_h,32 ,0,0,0,0);
		if (this->work == NULL)
		{
			std::cout << "Interface | Error->creat_work: " << SDL_GetError() << std::endl;
			return -1;
		}
		if (SDL_FillRect(this->work, NULL, SDL_MapRGB(this->work->format, 255, 255, 255)) == -1)
		{
			std::cout << "Interface | Error->creat_work: " << SDL_GetError() << std::endl;
			return -1;
		}
	}
	SDL_BlitSurface(this->work, NULL, this->screen, &this->pos);

	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | Error->creat_work: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_UpdateRect(this->screen, 0, 0, this->w_screen, this->h_screen);
	SDL_UpdateRect(this->work, 150, 25, this->work_w, 610);

	return 0;
}

char	c_interface::creat_opt()
{
	SDL_Rect	tmp;

	tmp = id::change_pos(this->pos, 5, 25, 140, 610);
	this->pos = tmp;
	this->opt = SDL_CreateRGBSurface(SDL_HWSURFACE, 140, 610 ,32 ,0,0,0,0);
	if (this->opt == NULL)
	{
		std::cout << "Interface | Error->creat_opt: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (SDL_FillRect(this->opt, NULL, SDL_MapRGB(this->opt->format, 30, 30, 30)) == -1)
	{
		std::cout << "Interface | Error->creat_opt: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_BlitSurface(this->opt, NULL, this->screen, &this->pos);

	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | Error->creat_opt: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_UpdateRect(this->screen, 0, 0, this->w_screen, this->h_screen);
	SDL_UpdateRect(this->opt, 5, 25, 140, 610);

	return 0;
}

char	c_interface::creat_actu_color_left()
{
	SDL_Rect	tmp;

	tmp = id::change_pos(this->pos, 86, 270, 16.5, 33);
	this->pos = tmp;
	this->actu_color_left = SDL_CreateRGBSurface(SDL_HWSURFACE, 16.5, 33, 32, 0, 0, 0 ,0);
	if (this->actu_color_left == NULL)
	{
		std::cout << "Interface | creat_actu_color_left | Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (SDL_FillRect(this->actu_color_left, NULL, color_pen_left) == -1)
	{
		std::cout << "Interface | creat_actu_color_left | Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_BlitSurface(this->actu_color_left, NULL, this->screen, &this->pos);

	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | creat_actu_color_left | Error(actu_color): " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_UpdateRect(this->screen, 0, 0, this->w_screen, this->h_screen);
	SDL_UpdateRect(this->actu_color_left, 86, 270, 16.5, 33);

	return 0;
}

char	c_interface::creat_actu_color_right()
{
	SDL_Rect	tmp;

	tmp = id::change_pos(this->pos, 102.5, 270, 16.5, 33);
	this->pos = tmp;
	this->actu_color_right = SDL_CreateRGBSurface(SDL_HWSURFACE, 16.5, 33, 32, 0, 0, 0 ,0);
	if (this->actu_color_right == NULL)
	{
		std::cout << "Interface | creat_actu_color_right | Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (SDL_FillRect(this->actu_color_right, NULL, color_pen_right) == -1)
	{
		std::cout << "Interface | creat_actu_color_right | Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_BlitSurface(this->actu_color_right, NULL, this->screen, &this->pos);

	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | creat_actu_color_right | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_UpdateRect(this->screen, 0, 0, this->w_screen, this->h_screen);
	SDL_UpdateRect(this->actu_color_right, 102.5, 270, 16.5, 33);

	return 0;
}

char	c_interface::creat_palette()
{
	SDL_Rect	tmp;

	tmp = id::change_pos(this->pos, 10, 35, 130, 230);
	this->pos = tmp;
	this->palette = SDL_LoadBMP("usual_picture/palette.bmp");
	if (this->palette == NULL)
	{
		std::cout << "Interface | creat_palette |Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_BlitSurface(this->palette, NULL, this->screen, &this->pos);

	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | creat_palette | Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_UpdateRect(this->screen, 0, 0, this->w_screen, this->h_screen);
	SDL_UpdateRect(this->palette, 10, 35, 130, 230);

	return 0;
}

char	c_interface::creat_new_popup()
{
	SDL_Rect	tmp;

	tmp = id::change_pos(this->pos, 200, 200, 500, 300);
	this->pos = tmp;
	this->tab = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 300 ,32 ,0,0,0,0);
	if (this->tab == NULL)
	{
		std::cout << "Interface | creat_new_popup | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	if (SDL_FillRect(this->tab, NULL, SDL_MapRGB(this->tab->format, 50, 50, 50)) == -1)
	{
		std::cout << "Interface | creat_new_popup | Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_BlitSurface(this->tab, NULL, this->screen, &this->pos);

	tmp = id::change_pos(this->pos, 320, 430, 100, 50);
	this->pos = tmp;
	this->ok = SDL_LoadBMP("usual_picture/ok.bmp");
	SDL_BlitSurface(this->ok, NULL, this->screen, &this->pos);
	if (this->ok == NULL)
	{
		std::cout << "Interface | creat_new_popup | Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	tmp = id::change_pos(this->pos, 520, 430, 100, 50);
	this->pos = tmp;
	this->close = SDL_LoadBMP("usual_picture/cancel.bmp");
	if (this->close == NULL)
	{
		std::cout << "Interface | creat_new_popup | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_BlitSurface(this->close, NULL, this->screen, &this->pos);

	SDL_UpdateRect(this->screen, 0, 0, this->w_screen, this->h_screen);
	SDL_UpdateRect(this->ok, 320, 430, 100, 50);
	SDL_UpdateRect(this->close, 520, 430, 100, 50);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | creat_new_popup | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	return 0;
}

void	c_interface::print_resize_ttf()
{
	SDL_Rect	tmp;
	SDL_Color	col;
	TTF_Init();

	this->font = TTF_OpenFont("LARGN___.TTF", 40);
	if (this->font == NULL)
	{
		std::cout << "Interface | print_resize_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}
	col = id::change_color(this->color, 0, 0, 0);
	this->color = col;

	tmp = id::change_pos(this->pos,200, 200, 500, 300);
	this->pos = tmp;
	this->msg = TTF_RenderText_Solid(this->font, "width: ", this->color);
	if (this->msg == NULL)
	{
		std::cout << "Interface | print_resize_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_BlitSurface(this->msg, NULL, this->screen, &this->pos);

	this->white = SDL_CreateRGBSurface(SDL_HWSURFACE, 180, 30, 32, 0,0,0,0);
	if (this->white == NULL)
	{
		std::cout << "Interface | print_resize_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}
	if (SDL_FillRect(this->white, NULL, SDL_MapRGB(this->white->format, 255, 255, 255)) == -1)
	{
		std::cout << "Interface | print_resize_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}

	tmp = id::change_pos(this->pos,380, 205, 500, 300);
	this->pos = tmp;
	SDL_BlitSurface(this->white, NULL, this->screen, &this->pos);

	tmp = id::change_pos(this->pos,416, 245, 500, 300);
	this->pos = tmp;
	SDL_BlitSurface(this->white, NULL, this->screen, &this->pos);

	tmp = id::change_pos(this->pos, 200, 240, 500, 300);
	this->pos = tmp;
	this->msg = TTF_RenderText_Solid(this->font, "height: ", this->color);
	if (this->msg == NULL)
	{
		std::cout << "Interface | print_resize_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_BlitSurface(this->msg, NULL, this->screen, &this->pos);

	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | print_resize_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}

	TTF_CloseFont(this->font);
	TTF_Quit();
}

char	c_interface::rezise_popup(SDL_Event event)
{
	int		stat;

	this->count = 0;
	this->pos_paramx = 380;
	this->save_posx_w = 380;
	this->save_posx_h = 425;
	this->pos_paramy = 200;
	stat = 1;

	print_resize_ttf();

	while (stat)
	{
		SDL_EnableUNICODE(1);
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN &&
		(event.motion.x >= 520) && (event.motion.y >= 430)
		&& (event.motion.x <= 620) && (event.motion.y <= 480))
		{
			SDL_FreeSurface(this->white);
			SDL_FreeSurface(this->close);
			SDL_FreeSurface(this->tab);
			SDL_FreeSurface(this->palette);
			SDL_FreeSurface(this->opt);
			SDL_FreeSurface(this->actu_color_left);
			SDL_FreeSurface(this->actu_color_right);
			SDL_FreeSurface(this->screen);
			run_surface(false,0);
			stat = 0;
		}
		else if (event.key.keysym.sym == SDLK_TAB)
		{
			if (this->count == 0)
			{
				this->count = 1;
				this->pos_paramx = this->save_posx_h;
			}
			else if (this->count == 1)
			{
				this->count = 0;
				this->pos_paramx = this->save_posx_w;
			}
		}
		else if (event.key.keysym.sym == SDLK_UP || ((event.type == SDL_MOUSEBUTTONDOWN)
			&& (event.motion.x > 380) && (event.motion.x < 680)
			&& (event.motion.y > 200) && (event.motion.y < 240)))
		{
			this->count = 0;
			this->pos_paramx = this->save_posx_w;
		}
		else if (event.key.keysym.sym == SDLK_DOWN || ((event.type == SDL_MOUSEBUTTONDOWN)
			&& (event.motion.x > 380) && (event.motion.x < 680)
			&& (event.motion.y > 240) && (event.motion.y < 280)))
		{
			this->count = 1;
			this->pos_paramx = this->save_posx_h;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (check_num(event) == 1)
				stat = 0;
			if (this->count == 2)
			{
				SDL_FreeSurface(this->white);
				SDL_FreeSurface(this->close);
				SDL_FreeSurface(this->tab);
				SDL_FreeSurface(this->palette);
				SDL_FreeSurface(this->actu_color_left);
				SDL_FreeSurface(this->actu_color_right);
				SDL_FreeSurface(this->opt);
				SDL_FreeSurface(this->screen);
				if (this->work_h > 610)
					this->h_screen = this->work_h + 30;
				else
					this->h_screen = 640;
				if (this->work_w > 745)
					this->w_screen = this->work_w + 155;
				else
					this->w_screen = 900;
				run_surface(true,0);
				std::cout << "*-----------------*" << std::endl;
				std::cout << "| rezise param ok |" << std::endl;
				std::cout << "*-----------------*" << std::endl;
				stat = 0;
			}
			else
			{
				run_surface(false,0);
				stat = 0;
			}
		}
	}
	return 0;
}

void	c_interface::print_name_ttf()
{
	SDL_Rect	tmp;
	SDL_Color	col;
	TTF_Init();

	this->font = TTF_OpenFont("LARGN___.TTF", 40);
	if (this->font == NULL)
	{
		std::cout << "Interface | print_name_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}
	col = id::change_color(this->color, 0, 0, 0);
	this->color = col;
	tmp = id::change_pos(this->pos,200, 200, 500, 300);
	this->pos = tmp;
	this->msg = TTF_RenderText_Solid(this->font, "NAME: ", this->color);
	if (this->msg == NULL)
	{
		std::cout << "Interface | print_name_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_BlitSurface(this->msg, NULL, this->screen, &this->pos);

	this->white = SDL_CreateRGBSurface(SDL_HWSURFACE, 490, 42, 32, 0,0,0,0);
	if (this->white == NULL)
	{
		std::cout << "Interface | print_name_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}
	if (SDL_FillRect(this->white, NULL, SDL_MapRGB(this->white->format, 255, 255, 255)) == -1)
	{
		std::cout << "Interface | print_name_ttf | Error: " << SDL_GetError() << std::endl;
		return;
	}
	tmp = id::change_pos(this->pos,205, 240, 500, 300);
	this->pos = tmp;
	SDL_BlitSurface(this->white,NULL,this->screen, &this->pos);

	tmp = id::change_pos(this->pos,205, 287, 500, 300);
	this->pos = tmp;
	SDL_BlitSurface(this->white,NULL,this->screen, &this->pos);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | print_name_ttf |Error: " << SDL_GetError() << std::endl;
		return;
	}
	TTF_CloseFont(this->font);
	TTF_Quit();
}

void	c_interface::print_size()
{
	SDL_Rect	tmp_pos;
	SDL_Color	col;
	char*		size;
	char*		tmp_size;
	TTF_Init();

	tmp_pos = id::change_pos(this->pos,121, 347, 30, 30);
	this->pos = tmp_pos;
	this->msg = SDL_CreateRGBSurface(SDL_HWSURFACE, 24, 30, 32, 0, 0, 0, 0);
	if (this->msg == NULL)
	{
		std::cout << "Interface |print_size | Error : " << SDL_GetError() << std::endl;
		return;
	}
	if (SDL_FillRect(this->msg, NULL, SDL_MapRGB(this->msg->format, 30, 30, 30)) == -1)
		return;
	SDL_BlitSurface(this->msg, NULL, this->screen, &this->pos);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | print_size |Error: " << SDL_GetError() << std::endl;
		return;
	}
	tmp_size = new char[3];
	size = id::itoa(this->size_tool, tmp_size, 10);
	if (size == NULL)
		return;
	this->font = TTF_OpenFont("LARGN___.TTF", 12);
	if (this->font == NULL)
	{
		std::cout << "Interface | print_size | Error: " << SDL_GetError() << std::endl;
		return;
	}
	col = id::change_color(this->color, 150, 150, 150);
	SDL_FreeSurface(this->msg);
	this->color = col;
	this->msg = TTF_RenderText_Solid(this->font, (const char*)size, this->color);
	if (this->msg == NULL)
	{
		std::cout << "Interface | print_size |Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_BlitSurface(this->msg, NULL, this->screen, &this->pos);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "Interface | print_size |Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_FreeSurface(this->msg);
	delete [] tmp_size ;
	TTF_CloseFont(this->font);
	TTF_Quit();
}

char	c_interface::save_popup(SDL_Event event)
{
	int		stat;

	this->pos_paramx = 200;
	this->pos_paramy = 240;
	stat = 1;

	print_name_ttf();

	while (stat)
	{
		SDL_EnableUNICODE(1);
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN &&
		(event.motion.x >= 520) && (event.motion.y >= 430)
		&& (event.motion.x <= 620) && (event.motion.y <= 480))
		{
			SDL_FreeSurface(this->white);
			SDL_FreeSurface(this->close);
			SDL_FreeSurface(this->tab);
			SDL_FreeSurface(this->palette);
			SDL_FreeSurface(this->actu_color_left);
			SDL_FreeSurface(this->actu_color_right);
			SDL_FreeSurface(this->opt);
			SDL_FreeSurface(this->screen);
			run_surface(false,0);
			stat = 0;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			check_path_save(event);
			SDL_FreeSurface(this->white);
			SDL_FreeSurface(this->close);
			SDL_FreeSurface(this->tab);
			SDL_FreeSurface(this->palette);
			SDL_FreeSurface(this->actu_color_left);
			SDL_FreeSurface(this->actu_color_right);
			SDL_FreeSurface(this->opt);
			SDL_FreeSurface(this->screen);
			run_surface(false,0);
			std::cout << "*---------------*" << std::endl;
			std::cout << "| save param ok |" << std::endl;
			std::cout << "*---------------*" << std::endl;
			stat = 0;
		}
	}
	return 0;
}

char	c_interface::load_popup(SDL_Event event)
{
	int	stat;

	this->pos_paramx = 200;
	this->pos_paramy = 240;
	stat = 1;

	print_name_ttf();

	while (stat)
	{
		SDL_EnableUNICODE(1);
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN &&
		   (event.motion.x >= 520) && (event.motion.y >= 430) &&
		   (event.motion.x <= 620) && (event.motion.y <= 480))
		{
			SDL_FreeSurface(this->white);
			SDL_FreeSurface(this->close);
			SDL_FreeSurface(this->tab);
			SDL_FreeSurface(this->palette);
			SDL_FreeSurface(this->actu_color_left);
			SDL_FreeSurface(this->actu_color_right);
			SDL_FreeSurface(this->opt);
			SDL_FreeSurface(this->screen);
			run_surface(false,0);
			stat = 0;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			check_path_load(event);
			if (this->work != NULL)
			{
				SDL_FreeSurface(this->white);
				SDL_FreeSurface(this->close);
				SDL_FreeSurface(this->tab);
				SDL_FreeSurface(this->palette);
				SDL_FreeSurface(this->actu_color_left);
				SDL_FreeSurface(this->actu_color_right);
				SDL_FreeSurface(this->opt);
				SDL_FreeSurface(this->screen);
				run_surface(false,0);
				std::cout << "*---------------*" << std::endl;
				std::cout << "| load param ok |" << std::endl;
				std::cout << "*---------------*" << std::endl;
				stat = 0;
			}
			else
			{
				load_it();
				run_surface(false,0);
				stat = 0;
			}
		}
	}
	return 0;
}


char	c_interface::run_surface(bool resize, const char* name)
{
	c_button	button;

	if (c_interface::creat_window() == -1)
	{
		perror("window");
		return -1;
	}
	if (resize == false)
	{
		if (c_interface::creat_work(name) == -1)
		{
			perror("work");
			return -1;
		}
		else if (c_interface::creat_work(name) == 1)
			return 1;
	}
	else if (resize == true)
	{
		if (c_interface::creat_work_resize() == -1)
		{
			perror("work");
			return -1;
		}
	}
	if (c_interface::creat_opt() == -1)
	{
		perror("opt");
		return -1;
	}
	if (c_interface::creat_actu_color_left() == -1)
	{
		perror("actu_color_left");
		return -1;
	}
	if (c_interface::creat_actu_color_right() == -1)
	{
		perror("actu_color_right");
		return -1;
	}
	if (c_interface::creat_palette() == -1)
	{
		perror("palette");
		return -1;
	}
	print_size();
	if (button.creat_button(button.button_new, "usual_picture/button_new_print.bmp", 5, 1, 70, 23) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_save, "usual_picture/button_save.bmp", 81, 1, 70, 23) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_load, "usual_picture/button_load.bmp", 156, 1, 70, 23) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_brush, "usual_picture/brush.bmp", 10, 308, 33, 33) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_pen, "usual_picture/crayon.bmp", 48, 308, 33, 33) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_pipette, "usual_picture/pipette.bmp", 10, 270, 33, 33) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_less, "usual_picture/less.bmp", 10, 347, 33, 33) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_current_size, "usual_picture/current_size.bmp", 48, 347, 33, 33) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_plus, "usual_picture/plus.bmp", 87, 347, 33, 33) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_padding, "usual_picture/padintg.bmp", 87, 308, 33, 33) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_rubber, "usual_picture/rubber.bmp", 10, 385, 33, 33) == -1)
	{
		perror("but");
		return -1;
	}
	if (button.creat_button(button.button_rectangle, "usual_picture/rectangle.bmp", 48, 385, 33, 33) == -1)
	{
		perror("buttton rectangle");
		return -1;
	}
	if (button.creat_button(button.button_circle, "usual_picture/circle.bmp", 87, 385, 33, 33) == -1)
	{
		perror("buttton ring of lord");
		return -1;
	}
	if (button.creat_button(button.button_lineh, "usual_picture/lineh.bmp", 10, 423, 33, 33) == -1)
	{
		perror("buttton line");
		return -1;
	}
	if (button.creat_button(button.button_linev, "usual_picture/linev.bmp", 48, 423, 33, 33) == -1)
	{
		perror("buttton line");
		return -1;
	}
	return 0;

}
