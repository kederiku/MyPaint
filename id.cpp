#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <exception>
#include "id.h"

int	id::error(const char* msg, int ret)
{
	if (msg)
	{
		write(2, msg, id::strlen(msg));
		write(2, "\n", 1);
	}
	return ret;
}

int	id::myperror(const char* msg)
{
	perror(msg);
	return (-1);
}

int	id::debug(const char* msg)
{
	write(1, msg, id::strlen(msg));
	write(1, "\n", 1);
	return 1;
}

int	id::strlen(const char* str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		++str;
		++counter;
	}
	return counter;
}

void	id::strcpy(char* dest, char* src)
{
	while (*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = 0;
}

void	id::copy_characters(char* dest, char* src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		*dest = *src;
		++i;
		++src;
		++dest;
	}
}

void	id::strncpy(char* dest, char* src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (*src && i < size)
	{
		*dest = *src;
		++dest;
		++src;
		i++;
	}
}


char	id::strcmp(const char* src, const char* cmp)
{
	int	i;

	i = 0;
	while (*(src + i) && *(src + i) == *(cmp + i))
		++i;
	if (*(src + i) < *(cmp + i))
		return (-1);
	else if (*(src + i) > *(cmp + i))
		return (1);
	return (0);
}

char	id::strncmp(char* src, char* cmp, unsigned int size)
{
	unsigned int	i;

	if (!src || !cmp || size == 0)
		return (0);
	i = 0;
	while (*(src + i) == *(cmp + i) && i < size)
		i++;
	if (i == size)
		return (0);
	else if (*(src + i) < *(cmp + i))
		return (-1);
	return (1);
}

char*	id::strstr(char* src, char* oc)
{
	unsigned int	i;

	if (!src || !oc)
		return (NULL);
	for (i = 0; *(src + i) != '\0'; i++)
	{
		if (!id::strncmp(src + i, oc, id::strlen(oc)))
			return (src + i);
	}
	return (NULL);
}

char*	id::strdup(char* todup)
{
	char*	dup;

	if (!todup)
		return (NULL);
	dup = new (std::nothrow) char[id::strlen(todup) + 1];
	if (dup == NULL)
		return (NULL);
	id::strcpy(dup, todup);
	dup[id::strlen(todup)] = '\0';
	return (dup);
}

char*	id::strndup(char* todup, unsigned int size)
{
	char*	dup;

	if (!todup || size == 0)
		return (NULL);
	dup = new (std::nothrow) char[size + 1];
	if (dup == NULL)
		return (NULL);
	id::strncpy(dup, todup, size);
	dup[size] = '\0';
	return (dup);
}

char*	id::strncat(char* dest, char* src, unsigned int len)
{
	unsigned int	i;
	unsigned int	destlen;

	destlen = id::strlen(dest);
	i = 0;
	while (*(src + i) != '\0' && i < len)
	{
		*(dest + destlen) = *(src + i);
		destlen++;
		i++;
	}
	*(dest + destlen) = '\0';
	return (dest);
}

int	id::atoi(char* str)
{
	int	number;
	int	neg;

	if (!str)
		return -1;
	neg = 0;
	number = 0;
	while (*str)
	{
		if (*str <= '9' && *str >= '0')
			number = number * 10 + (*str) - '0';
		else if (*str == '-')
			neg = neg + 1;
		str = str + 1;
	}
	if (neg % 2)
		return -number;
	else
		return number;
}

char*	id::itoa(int value, char* buf, int base)
{
	int	countA;
	int	current;
	int	nb_digit;

	countA = 1;
	current = 0;
	nb_digit = 0;
	while ((value / countA) >= base || (value / countA) <= -base)
	{
		countA = countA * base;
		nb_digit = nb_digit + 1;
	}
	if (buf == NULL)
		return NULL;
	while (countA >= 1)
	{
		if (value < 0)
		{
			buf[current] =  (((value / countA) % base) * -1 +'0');
			buf[0] = '0';
			current = current + 1;
		}
		else if (value > 0)
		{
			buf[current] = (value / countA) % base + '0';
			current = current + 1;
		}
		else
			buf[0] = '0';
		countA = countA / 10;
	}
	buf[nb_digit+1] = 0;
	return buf;
}

char*	id::strcat(char* dest_str, char* src_str)
{
	int	size;
	int	i;

	i = 0;
	size = id::strlen(dest_str);
	while (src_str[i] != 0)
	{
		dest_str[size + i] = src_str[i];
		i = i + 1;
	}
	dest_str[size + i] = 0;
	return dest_str;
}

char*	id::readfile(int fd, unsigned int size_to_read)
{
	char*	ret;
	int	nread;

	ret = new (std::nothrow) char [size_to_read];
	if (ret == NULL)
		return (NULL);
	nread = read(fd, ret, size_to_read);
	if (nread == -1)
		return (NULL);
	return (ret);
}

void	id::dump_word_tab(char** word_tab)
{
	for (unsigned int i = 0; word_tab[i] != 0; i++)
		id::debug(word_tab[i]);
}

void	id::clear_buffer(char* buffer, int size)
{
	for (int i = 0; i < size; i++)
		buffer[i] = '\0';
}

char*	id::rezise_buffer(char* buf, unsigned int size)
{
	char*	ret;

	ret = new char[size * 2];
	strcpy(ret, buf);
	delete [] buf;
	return ret;
}

SDL_Rect	id::change_pos(SDL_Rect pos, int x, int y, int w, int h)
{
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
	return pos;
}

SDL_Color	id::change_color(SDL_Color color, int r, int g, int b)
{
	color.r = r;
	color.g = g;
	color.b = b;
	return color;
}
