#include <unistd.h>
#include "interface.h"
#include "id.h"

void	c_interface::assign_param()
{
	if (this->num_buf == 1)
		this->work_w = this->save1;
	else
	{
		this->work_w = id::atoi(this->param1);
		this->save1 = this->work_w;
		std::cout << this->work_w << std::endl;
	}
	if (this->sec_num_buf == 1)
		this->work_h = this->save2;
	else
	{
		this->work_h = id::atoi(this->param2);
		this->save2 = this->work_h;
		std::cout << this->work_h << std::endl;
	}
}

void	c_interface::clean_resize()
{
	SDL_Surface	*clean;
	SDL_Rect	tmp;

	clean = SDL_CreateRGBSurface(SDL_HWSURFACE, 40, 30, 32,0,0,0,0);
	if (clean == NULL)
	{
		std::cout << "print_interface | clean_resize | Error: " << SDL_GetError() << std::endl;
		return;
	}

	if (SDL_FillRect(clean, NULL, SDL_MapRGB(clean->format,255,255,255)) == -1)
	{
		std::cout << "print_interface | clean_resize | Error: " << SDL_GetError() << std::endl;
		return;
	}

	if (this->count == 0)
	{
		this->pos_paramx -= 40;
		this->save_posx_w = this->pos_paramx;
		tmp = id::change_pos(this->pos, this->pos_paramx, 205, 20, 40);
		this->pos = tmp;
		SDL_BlitSurface(clean, NULL, this->screen, &this->pos);
	}
	else if (this->count == 1)
	{
		this->pos_paramx -= 40;
		this->save_posx_h = this->pos_paramx;
		tmp = id::change_pos(this->pos, this->pos_paramx, 245, 20, 40);
		this->pos = tmp;
		SDL_BlitSurface(clean, NULL, this->screen, &this->pos);
	}
	SDL_FreeSurface(clean);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "print_interface | clean_resize | Error: " << SDL_GetError() << std::endl;
		return;
	}
}

void	c_interface::clean_name()
{
	SDL_Surface	*clean;
	SDL_Rect	tmp;

	clean = SDL_CreateRGBSurface(SDL_HWSURFACE, 41, 42, 32,0,0,0,0);

	if (SDL_FillRect(clean, NULL, SDL_MapRGB(clean->format,255,255,255)) == -1)
	{
		std::cout << "print_interface | clean_name | Error: " << SDL_GetError() << std::endl;
		return;
	}

	if (this->pos_paramx <= 200 && this->pos_paramy == 240)
		return;
	this->pos_paramx -= 40;
	if (this->pos_paramx < 200 && this->pos_paramy == 280)
	{
		this->pos_paramx = 640;
		this->pos_paramy = 240;
	}
	tmp = id::change_pos(this->pos, this->pos_paramx + 5, this->pos_paramy, 20, 40);
	this->pos = tmp;
	SDL_BlitSurface(clean, NULL, this->screen, &this->pos);
	SDL_FreeSurface(clean);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "print_interface | clean_name | Error: " << SDL_GetError() << std::endl;
		return;
	}
}

void	c_interface::save_it()
{
	SDL_Surface*	copy;

	SDL_SaveBMP(this->work, this->save_temp);
	this->work = SDL_LoadBMP(this->save_temp);
	if (this->work == NULL)
	{
		std::cout << "print_interface | save_it | Error: " << SDL_GetError() << std::endl;
		return;
	}
	copy = SDL_CreateRGBSurface(SDL_HWSURFACE,this->work_w,this->work_h,32,0,0,0,0);
	if (copy == NULL)
	{
		std::cout << "print_interface | save_it | Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_BlitSurface(this->work,NULL,copy,0);
	SDL_FreeSurface(this->work);
	this->work = copy;
}

void	c_interface::load_it()
{
	SDL_Surface*	copy;

	SDL_FreeSurface(this->work);
	this->work = SDL_LoadBMP(this->save_temp);
	if (this->work == NULL)
	{
		std::cout << "print_interface | load_it | Error: " << SDL_GetError() << std::endl;
		return;
	}
	copy = SDL_CreateRGBSurface(SDL_HWSURFACE,this->work_w,this->work_h,32,0,0,0,0);
	if (copy == NULL)
	{
		std::cout << "print_interface | load_it | Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_BlitSurface(this->work,NULL,copy,0);
	SDL_FreeSurface(this->work);
	this->work = copy;
}

char	c_interface::check_num(SDL_Event event)
{
	int	stop;

	this->num_buf = 1;
	this->sec_num_buf = 1;
	stop = 0;
	save_it();
	while (this->count < 2 && stop == 0)
	{
		this->c = event.key.keysym.unicode;
		SDL_WaitEvent(&event);
		if ((event.type == SDL_KEYUP) && ((this->num_buf < 5 && this->count == 0) || (this->sec_num_buf < 5 && this->count == 1)) &&
		((event.key.keysym.sym == SDLK_KP0) ||
		(event.key.keysym.sym == SDLK_KP1) ||
		(event.key.keysym.sym == SDLK_KP2) ||
		(event.key.keysym.sym == SDLK_KP3) ||
		(event.key.keysym.sym == SDLK_KP4) ||
		(event.key.keysym.sym == SDLK_KP5) ||
		(event.key.keysym.sym == SDLK_KP6) ||
		(event.key.keysym.sym == SDLK_KP7) ||
		(event.key.keysym.sym == SDLK_KP8) ||
		(event.key.keysym.sym == SDLK_KP9)))
		{
			print_num();
			this->pos_paramx += 40;
			add_resize();
			if (this->count == 0)
			{
				this->save_posx_w = this->pos_paramx;
				this->num_buf += 1;
			}
			if (this->count == 1)
			{
				this->save_posx_h = this->pos_paramx;
				this->sec_num_buf += 1;
			}
		}
		else if((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_TAB))
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
		else if(((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_UP)) ||
			((event.type == SDL_MOUSEBUTTONDOWN)
			&& (event.motion.x > 380) && (event.motion.x < 680)
			&& (event.motion.y > 200) && (event.motion.y < 240)))
		{
			this->count = 0;
			this->pos_paramx = this->save_posx_w;
		}
		else if(((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_DOWN)) ||
			((event.type == SDL_MOUSEBUTTONDOWN)
			&& (event.motion.x > 380) && (event.motion.x < 680)
			&& (event.motion.y > 240) && (event.motion.y < 280)))
		{
			this->count = 1;
			this->pos_paramx = this->save_posx_h;
		}
		else if ((event.type == SDL_KEYUP) && ((event.key.keysym.sym == SDLK_RETURN)||
							(event.key.keysym.sym == SDLK_KP_ENTER)))
		{
			if (this->count == 1)
				assign_param();
			this->pos_paramx = 380;
			this->count += 1;
			if (this->count == 1)
				this->pos_paramx = 425;
		}
		else if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_BACKSPACE))
		{
			if (this->num_buf > 1 && this->count == 0)
			{
				sub_resize();
				this->num_buf -= 1;
				clean_resize();
			}
			else if (this->sec_num_buf > 1 && this->count == 1)
			{
				sub_resize();
				this->sec_num_buf -= 1;
				clean_resize();
				std::cout << "hello"<< std::endl;
			}
		}
		else if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_ESCAPE))
		{
			this->work_w = this->save1;
			this->work_h = this->save2;
			load_it();
			stop += 1;
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x >= 320) && (event.motion.y >= 430)
			&& (event.motion.x <= 420) && (event.motion.y <= 480))
		{
			assign_param();
			count = 2;
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x >= 520) && (event.motion.y >= 430)
			&& (event.motion.x <= 620) && (event.motion.y <= 480))
		{
			this->work_w = this->save1;
			this->work_h = this->save2;
			load_it();
			stop += 1;
		}
	}
	return 0;
}

void	c_interface::add_resize()
{
	const char*	tmp;
	int		num;

	num = 0;
	if (this->count == 0)
	{
		if (this->num_buf == 1)
		{
			this->param1 = new char [2];
			this->param1[0] = this->c;
			this->param1[1] = this->c;
		}
		else
		{
			tmp = this->param1;
			this->param1 = new char [this->num_buf + 1];
			while (num < this->num_buf)
			{
				this->param1[num] = tmp[num];
				num += 1;
			}
			this->param1[this->num_buf - 1] = this->c;
			this->param1[this->num_buf] = '\0';
		}
	}
	else if (this->count == 1)
	{
		if (this->sec_num_buf == 1)
		{
			this->param2 = new char [2];
			this->param2[0] = this->c;
			this->param2[1] = this->c;
		}
		else
		{
			tmp = this->param2;
			this->param2 = new char [this->sec_num_buf + 1];
			while (num < this->sec_num_buf)
			{
				this->param2[num] = tmp[num];
				num += 1;
			}
			this->param2[this->sec_num_buf - 1] = this->c;
			this->param2[this->sec_num_buf] = '\0';
		}
	}
}

void	c_interface::sub_resize()
{
	const char*	tmp;
	int		num;

	num = 0;
	if (this->count == 0)
	{
		if (this->num_buf > 1)
		{
			tmp = this->param1;
			this->param1 = new char[this->num_buf - 1];
			while(num < (this->num_buf - 1))
			{
				this->param1[num] = tmp[num];
				num += 1;
			}
			this->param1[this->num_buf - 2] = '\0';
		}
	}
	else if (this->count == 1)
	{
		if (this->sec_num_buf > 1)
		{
			tmp = this->param2;
			this->param2 = new char[this->sec_num_buf - 1];
			while(num < (this->sec_num_buf - 1))
			{
				this->param2[num] = tmp[num];
				num += 1;
			}
			this->param2[this->sec_num_buf - 2] = '\0';
		}
	}
}

char	c_interface::check_path_save(SDL_Event event)
{
	int		stat;
	SDL_Rect	tmp;

	stat = 1;
	this->num_buf = 1;
	SDL_EnableUNICODE(1);
	save_it();
	while (stat)
	{
		this->c = event.key.keysym.unicode;
		SDL_WaitEvent(&event);
		if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_RETURN))
		{
			if (this->num_buf > 1)
			{
				std::cout <<"check_path_save | buffer = \""<< this->buffer <<"\"" << std::endl;
				if (SDL_SaveBMP(this->work, this->buffer) == -1)
				{
					std::cout << "print_interface | check_path_save | Error: " << SDL_GetError() << std::endl;
					return -1;
				}
			}
			run_surface(false,0);
			stat = 0;
		}
		else if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_BACKSPACE))
		{
			if (this->num_buf > 1)
			{
				sub_name();
				this->num_buf -= 1;
				if (this->pos_paramx == 200)
				{
					this->pos_paramx = 680;
					this->pos_paramy = 240;
				}
				clean_name();
			}
		}
		else if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_ESCAPE))
		{
			load_it();
			stat = 0;
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x >= 520) && (event.motion.y >= 430)
			&& (event.motion.x <= 620) && (event.motion.y <= 480))
		{
			load_it();
			stat = 0;
		}
		else if (event.type == SDL_KEYUP && this->num_buf <= 24)
		{
			print_name();
			add_name();
			this->pos_paramx += 40;
			this->num_buf += 1;
			if (this->pos_paramx >= 680 && this->pos_paramy == 240)
			{
				this->pos_paramx = 200;
				this->pos_paramy = 287;
				tmp = id::change_pos(this->pos, this->pos_paramx, this->pos_paramy, 20, 40);
				this->pos = tmp;
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x >= 320) && (event.motion.y >= 430)
			&& (event.motion.x <= 420) && (event.motion.y <= 480))
		{
			if (this->num_buf > 1)
			{
				std::cout <<"check_path_save | buffer = \""<< this->buffer <<"\"" << std::endl;
				if (SDL_SaveBMP(this->work, this->buffer) == -1)
				{
					std::cout << "print_interface | check_path_save | Error: " << SDL_GetError() << std::endl;
					return -1;
				}
			}
			run_surface(false,0);
			stat = 0;
		}
	}
	return 0;
}

char	c_interface::check_path_load(SDL_Event event)
{
	int		stat;
	SDL_Rect	tmp;
	SDL_Surface*	copy;

	stat = 1;
	this->num_buf = 1;
	SDL_EnableUNICODE(1);
	save_it();
	while (stat)
	{
		this->c = event.key.keysym.unicode;
		SDL_WaitEvent(&event);
		if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_RETURN))
		{
			if (this->num_buf > 1)
			{
				SDL_FreeSurface(this->work);
				this->work = SDL_LoadBMP(this->buffer);
				if (this->work == NULL)
				{
					std::cout << "print_interface | check_path_load | Error: " << SDL_GetError() << std::endl;
					return -1;
				}
			}
			if (this->num_buf > 1 && this->work != NULL)
			{
				std::cout << "check_path_load | new size od work -> width : "<< this->work->w << " | height : " << this->work->h << std::endl;
				copy = SDL_CreateRGBSurface(SDL_HWSURFACE, this->work->w, this->work->h, 32, 0,0,0,0);
				if (copy == NULL)
				{
					std::cout << "print_interface | check_path_load | Error: " << SDL_GetError() << std::endl;
					return -1;
				}
				SDL_BlitSurface(this->work,NULL,copy,0);
				SDL_FreeSurface(this->work);
				this->work = copy;
				this->work_w = this->work->w;
				this->work_h = this->work->h;
				this->save1 = this->work_w;
				this->save2 = this->work_h;
			}
			else if (this->num_buf > 1 && this->work == NULL)
			{
				SDL_FreeSurface(this->close);
				SDL_FreeSurface(this->tab);
				creat_new_popup();
				print_name_ttf();
				load_it();
				this->num_buf = 1;
				std::cout << "check_path_load | NOP your file is a big shit" << std::endl;
			}
			else if (this->num_buf == 0)
				run_surface(false,0);
			stat = 0;
		}
		else if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_BACKSPACE))
		{
			if (this->num_buf > 1)
			{
				sub_name();
				this->num_buf -= 1;
				if (this->pos_paramx == 200)
				{
					this->pos_paramx = 680;
					this->pos_paramy = 240;
				}
				clean_name();
			}
		}
		else if ((event.type == SDL_KEYUP) && (event.key.keysym.sym == SDLK_ESCAPE))
		{
			load_it();
			stat = 0;
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x >= 520) && (event.motion.y >= 430)
			&& (event.motion.x <= 620) && (event.motion.y <= 480))
		{
			load_it();
			stat = 0;
		}
		else if (event.type == SDL_KEYUP && this->num_buf <= 24)
		{
			print_name();
			add_name();
			this->pos_paramx += 40;
			this->num_buf += 1;
			if (this->pos_paramx >=680 && this->pos_paramy == 240)
			{
				this->pos_paramx = 200;
				this->pos_paramy = 287;
				tmp = id::change_pos(this->pos, this->pos_paramx, this->pos_paramy, 20, 40);
				this->pos = tmp;
			}
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN && (event.motion.x >= 320) && (event.motion.y >= 430)
			&& (event.motion.x <= 420) && (event.motion.y <= 480))
		{
			if (this->num_buf > 1)
			{
				SDL_FreeSurface(this->work);
				this->work = SDL_LoadBMP(this->buffer);
				if (this->work == NULL)
				{
					std::cout << "print_interface | check_path_load | Error: " << SDL_GetError() << std::endl;
					return -1;
				}
			}
			if (this->num_buf > 1 && this->work != NULL)
			{
				std::cout << "check_path_load | new size od work -> width : "<< this->work->w << " | height : " << this->work->h << std::endl;
				copy = SDL_CreateRGBSurface(SDL_HWSURFACE, this->work->w, this->work->h, 32, 0,0,0,0);
				if (copy == NULL)
				{
					std::cout << "print_interface | check_path_load | Error: " << SDL_GetError() << std::endl;
					return -1;
				}
				SDL_BlitSurface(this->work,NULL,copy,0);
				SDL_FreeSurface(this->work);
				this->work = copy;
				this->work_w = this->work->w;
				this->work_h = this->work->h;
				this->save1 = this->work_w;
				this->save2 = this->work_h;
				stat = 0;
			}
			else if (this->num_buf > 1 && this->work == NULL)
			{
				SDL_FreeSurface(this->close);
				SDL_FreeSurface(this->tab);
				creat_new_popup();
				print_name_ttf();
				load_it();
				this->num_buf = 1;
				std::cout << "check_path_load | NOP your file is a big shit" << std::endl;
			}
			else if (this->num_buf == 0)
				run_surface(false,0);
			stat = 0;
		}
	}
	return 0;
}

char	c_interface::print_num()
{
	SDL_Rect	tmp;
	SDL_Color	col;
	char*		ch;

	ch = new char[2];
	ch[0] = this->c;
	ch[1] = '\0';
	col = id::change_color(this->color, 0, 0, 0);
	this->color = col;
	if (this->count == 0)
	{
		tmp = id::change_pos(this->pos, this->pos_paramx, this->pos_paramy, 500, 300);
		this->pos = tmp;
	}
	else if (this->count == 1)
	{
		tmp = id::change_pos(this->pos, this->pos_paramx , this->pos_paramy + 40, 500, 300);
		this->pos = tmp;
	}
	TTF_Init();
	this->font = TTF_OpenFont("LARGN___.TTF", 40);
	if (this->font == NULL)
	{
		std::cout << "print_interface | print_num | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	this->msg = TTF_RenderText_Solid(this->font, ch, this->color);
	if (this->msg == NULL)
	{
		std::cout << "print_interface | print_num | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_BlitSurface(this->msg, NULL, this->screen, &this->pos);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "print_interface | print_num | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	TTF_CloseFont(this->font);
	TTF_Quit();
	delete [] ch;
	return this->c;
}

char	c_interface::print_name()
{
	SDL_Rect	tmp;
	SDL_Color	col;
	char*		ch;

	ch = new char[2];
	ch[0] = this->c;
	ch[1] = '\0';
	col = id::change_color(this->color, 0, 0, 0);
	this->color = col;
	tmp = id::change_pos(this->pos, this->pos_paramx + 5, this->pos_paramy+2, 500, 300);
	this->pos = tmp;

	TTF_Init();
	this->font = TTF_OpenFont("LARGN___.TTF", 40);
	if (this->font == NULL)
	{
		std::cout << "print_interface | print_name | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	this->msg = TTF_RenderText_Solid(this->font, ch, this->color);
	if (this->msg == NULL)
	{
		std::cout << "print_interface | print_name | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_BlitSurface(this->msg, NULL, this->screen, &this->pos);
	if (SDL_Flip(this->screen) == -1)
	{
		std::cout << "print_interface | print_name | Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	TTF_CloseFont(this->font);
	TTF_Quit();
	delete [] ch;
	return this->c;
}

char*	c_interface::add_name()
{
	const char*	tmp;
	int		num;

	num = 0;
	if (this->num_buf == 1)
	{
		this->buffer = new char [2];
		this->buffer[0] = this->c;
		this->buffer[1] = this->c;
	}
	else
	{
		tmp = this->buffer;
		this->buffer = new char [this->num_buf + 1];
		while (num < this->num_buf)
		{
			this->buffer[num] = tmp[num];
			num += 1;
		}
		this->buffer[this->num_buf - 1] = this->c;
		this->buffer[this->num_buf] = '\0';
	}
	return this->buffer;
}

char*	c_interface::sub_name()
{
	const char*	tmp;
	int		num;

	num = 0;
	if (this->num_buf > 1)
	{
		tmp = this->buffer;
		this->buffer = new char[this->num_buf - 1];
		while(num < (this->num_buf - 1))
		{
			this->buffer[num] = tmp[num];
			num += 1;
		}
		this->buffer[this->num_buf - 2] = '\0';
	}
	return this->buffer;
}

char	c_interface::print_key()
{
	SDL_Event	event;
	char		c;
	int		go;

	go = 1;
	SDL_EnableUNICODE(1);
	while (go)
	{
		c = event.key.keysym.unicode;
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYUP)
		{
			go = 0;
		}
	}
	return c;
}
