#ifndef __ID__
#define __ID__

#include <SDL/SDL.h>

namespace	id
{
	void		copy_characters(char* dest, char* src, unsigned int size);
	int		error(const char* msg, int ret);
	int		myperror(const char* msg);
	int		debug(const char*);
	int		strlen(const char* str);
	void		strcpy(char* dest, char* src);
	void		strncpy(char* dest, char* src, unsigned int size);
	char		strcmp(const char*, const char*);
	char		strncmp(char*, char*, unsigned int);
	char*		strstr(char*, char*);
	char*		strdup(char*);
	char*		strndup(char*, unsigned int);
	char*		strcat(char* dest_str, char* src_str);
	int		atoi(char* nb);
	char*		itoa(int value, char* buf, int base);
	char*		strncat(char* dest, char* src, unsigned int len);
	char**		id_str_to_word_tab_char(char* str, char* charset);
	char*		readfile(int, unsigned int);
	void		dump_word_tab(char**);
	char*		rezise_buffer(char* buf, unsigned int size);
	void		clear_buffer(char*, int);
	SDL_Rect	change_pos(SDL_Rect pos, int x, int y, int w, int h);
	SDL_Color	change_color(SDL_Color color, int r, int g, int b);
}

#endif
