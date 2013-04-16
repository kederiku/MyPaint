#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

class c_button;

class 	c_interface
{
private:
	SDL_Surface	*opt;
	SDL_Event	event;
	SDL_Surface	*msg;
	SDL_Surface	*tab;
	SDL_Surface	*close;
	SDL_Surface	*ok;
	SDL_Surface	*white;
	TTF_Font*	font;
	SDL_Surface*	palette;
	SDL_Surface*	screen;

	int		name_change;
	int		num_buf;
	int		sec_num_buf;
	char		c;
	int		pos_paramx;
	int		pos_paramy;
	int		save_posx_w;
	int		save_posx_h;
	const char*	save_temp;

public:
	int		type_tool;//				->>CASSE LES COUILLES!
	unsigned long	color_pen_left;//				->> PAS REUSSI :lvalue required as left operand of assignment
	unsigned long	color_pen_right;//				->> PAS REUSSI :lvalue required as left operand of assignment
//	unsigned long	color_cible;//				->> WTF la variable est mm pas utiliser dans interface!!!!!
	int		tmp_tool;
	int		size_tool;
	int		save1;
	int		save2;
	char*		param1;
	char*		param2;
	int		work_w;
	int		work_h;
	int		count_param;
	char*		buffer;
	SDL_Color	color;
	SDL_Rect	pos;
	SDL_Rect	work_pos;
	int		w_screen;
	int		h_screen;
	int		count;

	SDL_Surface*	actu_color_left;
	SDL_Surface*	actu_color_right;
	SDL_Surface*	color_cursor;
	SDL_Rect	position_color_cursor;
	SDL_Rect	position_source;
	SDL_Rect	position_dest;
	c_interface();
	~c_interface();
	SDL_Surface	*work;
	void		print_resize_ttf();
	void		print_name_ttf();
	void		save_it();
	void		load_it();
	void		save_param();
	void		assign_param();
	void		clean_resize();
	void            clean_name();
	char		check_num(SDL_Event event);
	char            check_path_save(SDL_Event event);
	char            check_path_load(SDL_Event event);
	char		print_num();
	char		creat_window();
	char		creat_work(const char* name);
	char            creat_work_resize();
	char		creat_opt();
	char		creat_palette();
	char		creat_actu_color_left();
	char		creat_actu_color_right();
	char		print_key();
	char		print_name();
	void		add_resize();
	void		sub_resize();
	char*           add_name();
	char*           sub_name();		//->ancien sous_name
	char		creat_new_popup();
	char		rezise_popup(SDL_Event event);
	char		save_popup(SDL_Event event);
	char            load_popup(SDL_Event event);
	void		print_size();
	char		run_surface(bool resize, const char* name);
	SDL_Surface*	get_screen()
	{
		return this->screen;
	}
	SDL_Surface*	get_palette()
	{
		return this->palette;
	}
//	SDL_Surface*	get_opt()
//	{
//		return this->opt;
//	}
};
#endif
